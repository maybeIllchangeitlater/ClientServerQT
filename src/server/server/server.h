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
  explicit Server(Controller &controller, QString &projectDir, QObject *parent = nullptr)
      : _controller(controller), _projectDir(projectDir), QTcpServer(parent) {}

 protected:
  /**
   * @brief incomingConnection принимает входящие соединение
   * @param socketDescriptor описание сокета клиента
   */
  void incomingConnection(qintptr socketDescriptor) override;

 private slots:
  /**
   * @brief processRequest обрабатывает запрос посланный клиентом (POST 1 из 3
   * типов даты или GET количества сообщений принятых сервером/view из бд)
   */
  void processRequest();

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
                   QTcpSocket *socket, const QString &connectionStatus);
  /**
   * @brief writeResponse записывает ответ клиенту
   * @param data ответ
   * @param socket клиентский сокет
   * @param connectionStatus держать ли соединений открытым
   */
  void writeResponse(const QString &data, QTcpSocket *socket,
                     const QString &connectionStatus);
  /**
   * @brief parseURI извлекает идентефикатор ресурсов из пришедшего реквеста
   * @param requestData реквест
   * @return путь
   */
  QString parseURI(const QByteArray &requestData) const;
  /**
   * @brief getConnectionStatus извлекает статус подключения из пришедшего
   * реквеста
   * @param requestData реквест
   * @return статус подключения
   */
  QString parseConnectionStatus(const QByteArray &requestData) const;

 private:
  Controller &_controller;
  QString &_projectDir;
};
}  // namespace test
#endif  // CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
