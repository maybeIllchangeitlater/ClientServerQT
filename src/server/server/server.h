#ifndef CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
#define CLIENTSERVERQT_SERVER_SERVER_SERVER_H_

#include <QByteArray>
#include <QDebug>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUrl>

#include "../common/constants/URI.h"
#include "../common/constants/httpHeaderConstants.h"
#include "../controller/controller.h"

namespace test {

/**
 * @brief The Server class предоставляющий функционал сервера для передачи и
 * получения данных от клиента
 */
class Server : public QTcpServer {
  Q_OBJECT
 public:
  /**
   * @brief Server конструктор принимающий в себя контроллер
   * @param controller объект предоставляющий для выполнения различных запросов
   * к базе данных
   */
  explicit Server(Controller &controller, QObject *parent = nullptr)
      : _controller(controller), QTcpServer(parent) {}

 protected:
  /**
   * @brief incomingConnection принимает входящие соединение
   * @param socketDescriptor описание сокета клиента
   */
  void incomingConnection(qintptr socketDescriptor) override {
    qDebug() << "new client connected " << socketDescriptor;
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::processRequest);

    connect(socket, &QTcpSocket::disconnected, socket,
            &QTcpSocket::deleteLater);
  }

 private slots:
  /**
   * @brief processRequest обрабатывает запрос посланный клиентом (POST 1 из 3
   * типов даты или GET количества сообщений принятых сервером/view из бд)
   */
  void processRequest() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QByteArray requestData = socket->readAll();
    QString path = parseURI(requestData);
    QString connectionStatus = parseConnectionStatus(requestData);

    if (path == http::uri::STRING) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postString(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::JSON) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postJson(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::BINARY) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postBinary(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::MESSAGE_COUNT) {
      workRequest(
          [&](const QByteArray &) { return _controller.getMessageCount(); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::VIEW) {
      workRequest([&](const QByteArray &) { return _controller.getView(); },
                  requestData, socket, connectionStatus);
    } else if (path == http::uri::CLOSE_CONNECTION) {
      socket->write(http::headers::HEADER_OK);
      writeResponse("", socket, http::headers::CONNECTION_STATUS_CLOSE);
    }
  }

 private:
  /**
   * @brief workRequest обрабатывает запросы клиента
   * @param handler какой метод контроллера должен обработать запрос
   * @param data запрос
   * @param socket клиентский сокет
   * @param connectionStatus держать ли соединений открытым
   */
  template <typename Handler>
  void workRequest(const Handler &handler, const QByteArray &data,
                   QTcpSocket *socket, const QString &connectionStatus) {
    try {
      QByteArray response = handler(data);
      socket->write(http::headers::HEADER_OK);
      writeResponse(response, socket, connectionStatus);
    } catch (const std::exception &e) {
      socket->write(http::headers::HEADER_BAD_REQUEST);
      writeResponse(e.what(), socket, http::headers::CONNECTION_STATUS_CLOSE);
    }
  }
  /**
   * @brief writeResponse записывает ответ клиенту
   * @param data ответ
   * @param socket клиентский сокет
   * @param connectionStatus держать ли соединений открытым
   */
  void writeResponse(const QString &data, QTcpSocket *socket,
                     const QString &connectionStatus) {
    if (!data.isEmpty()) {
      socket->write(http::headers::CONTENT_LENGTH_HEADER +
                    QByteArray::number(data.size()) +
                    http::headers::HEADER_DELIMITER);
      socket->write(http::headers::CONTENT_TYPE_HEADER);
      socket->write(http::headers::PLAIN_TEXT);
      socket->write(http::headers::HEADERS_END);
      socket->write(data.toUtf8());
    } else {
      socket->write(http::headers::CONTENT_LENGTH_HEADER +
                    QByteArray::number(0));
      socket->write(http::headers::HEADERS_END);
    }
    socket->flush();
    socket->waitForBytesWritten();
    if (connectionStatus == http::headers::CONNECTION_STATUS_CLOSE) {
      qDebug() << "im out";
      socket->disconnectFromHost();
    }
  }
  /**
   * @brief parseURI извлекает идентефикатор ресурсов из пришедшего реквеста
   * @param requestData реквест
   * @return путь
   */
  QString parseURI(const QByteArray &requestData) const {
    qsizetype pathIndex = requestData.indexOf('/');
    qsizetype protocolIndex = requestData.indexOf("HTTP/1.1");
    if (pathIndex != -1 && protocolIndex != -1 && protocolIndex > pathIndex) {
      return requestData.mid(pathIndex,
                             requestData.indexOf("HTTP/1.1") - pathIndex - 1);
    } else {
      throw std::logic_error("invalid HTTP request");
    }
  }
  /**
   * @brief getConnectionStatus извлекает статус подключения из пришедшего
   * реквеста
   * @param requestData реквест
   * @return статус подключения
   */
  QString parseConnectionStatus(const QByteArray &requestData) const {
    qsizetype connectionHeaderIndex =
        requestData.indexOf(http::headers::CONNECTION_HEADER);
    if (connectionHeaderIndex != -1) {
      qsizetype connectionHeaderEndIndex = requestData.indexOf(
          http::headers::HEADER_DELIMITER, connectionHeaderIndex);
      if (connectionHeaderEndIndex != -1) {
        QString connectionHeader =
            requestData.mid(connectionHeaderIndex,
                            connectionHeaderEndIndex - connectionHeaderIndex);
        QString status = connectionHeader.split(":").last().trimmed();
        return status;
      }
    }
    throw std::logic_error("invalid HTTP request");
  }
  Controller &_controller;
};
}  // namespace test
#endif  // CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
