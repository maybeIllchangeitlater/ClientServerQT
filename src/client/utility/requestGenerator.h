#ifndef CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>

#include "../common/constants/URI.h"
#include "../common/constants/httpHeaderConstants.h"
#include "../common/data.h"
#include "../common/dateTime.h"

namespace test {
namespace http {
/**
 * @brief The RequestGenerator class предоставляющий функциональность генерации
 * HTTP запросов
 */
class RequestGenerator {
 public:
  /**
   * @brief The ConnectionStatus enum предостовляющий статусы соединения
   */
  enum ConnectionStatus { KEEP_ALIVE, CLOSE };
  /**
   * @brief setHostPort устанавливает порт к которому отправляется запрос
   * @param hostPort порт к которому отправляется запрос
   */
  void setHostPort(unsigned short hostPort) noexcept { _hostPort = hostPort; }
  /**
   * @brief setHostHost устанавливает адрес удаленного хоста
   * @param hostHost адрес
   */
  void setHostHost(const QString &hostHost) {
    if (hostHost == "localhost") {
      _hostHost = "http://127.0.0.1:";
    } else if (!hostHost.startsWith("http://")) {
      _hostHost = "http://" + hostHost;
    } else {
      _hostHost = hostHost + ":";
    }
  }

  template <typename T>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest(
      T &&data, ConnectionStatus connectionStatus) {
    throw std::logic_error(std::string("Data type not supported: ") +
                           typeid(data).name());
  }

  /**
   * @brief generatePostRandomStringRequest генерирует POST запрос
   * строки
   * @return пару из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QString>(
      QString &&string, ConnectionStatus connectionStatus) {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::STRING);
    QNetworkRequest request(url);

    auto body = string.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, headers::PLAIN_TEXT);
    request.setRawHeader(headers::CONNECTION_HEADER,
                         getConnectionStatus(connectionStatus));
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(body.length()));

    return std::make_pair(std::move(request), std::move(body));
  }
  /**
   * @brief generatePostRandomJsonRequest генерирует POST запрос структуры Data
   * в виде json
   * @return пара из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QJsonObject>(
      QJsonObject &&jsonObj, ConnectionStatus connectionStatus) {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::JSON);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      headers::APPLICATION_JSON);
    request.setRawHeader(headers::CONNECTION_HEADER,
                         getConnectionStatus(connectionStatus));
    QJsonDocument doc(jsonObj);
    QByteArray byteArrayJson = doc.toJson();
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(byteArrayJson.length()));

    return std::make_pair(std::move(request), std::move(byteArrayJson));
  }

  /**
   * @brief generatePostBinaryRequest генерирует POST запрос содержимого
   * бинарного файла
   * @param binaryFilepath путь к бинарному файлу
   * @return пара из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QFile>(
      QFile &&binaryFile, ConnectionStatus connectionStatus) {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::BINARY);
    QNetworkRequest request(url);

    QByteArray body = binaryFile.readAll();

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      headers::APPLICATION_OCTETSTREAM);
    request.setRawHeader(headers::CONNECTION_HEADER,
                         getConnectionStatus(connectionStatus));
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(body.length()));

    return std::make_pair(std::move(request), std::move(body));
  }
  /**
   * @brief getMessageCountRequest генерирует GET запрос на количество сообщений
   * в дб
   * @return запрос
   */
  QNetworkRequest getMessageCountRequest() {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::MESSAGE_COUNT);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    return request;
  }
  /**
   * @brief getViewRequest генерирует GET запрос на view
   * @return запрос
   */
  QNetworkRequest getViewRequest() {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::VIEW);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    return request;
  }
  /**
   * @brief closeSessionRequest генерирует запрос на закрытие соединения
   * @return запрос
   */
  QNetworkRequest closeSessionRequest() {
    QUrl url(_hostHost + QString::number(_hostPort) + uri::CLOSE_CONNECTION);
    QNetworkRequest request(url);
    request.setRawHeader(headers::CONNECTION_HEADER,
                         headers::CONNECTION_STATUS_CLOSE);
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    return request;
  }

 private:
  QByteArray getConnectionStatus(ConnectionStatus connectionStatus) {
    return connectionStatus == KEEP_ALIVE ? headers::CONNECTION_STATUS_ALIVE
                                          : headers::CONNECTION_STATUS_CLOSE;
  }

 private:
  QString _hostHost;
  unsigned short _hostPort;
};

}  // namespace http
}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
