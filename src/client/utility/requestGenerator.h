#ifndef CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>

#include "../common/data.h"
#include "../common/dateTime.h"

namespace test {
namespace http {

class RequestGenerator {
  constexpr static const char *STRING_URL = "/text-data";
  constexpr static const char *JSON_URL = "/structured-data";
  constexpr static const char *BINARY_URL = "/file-upload";
  constexpr static const char *MESSAGE_COUNT_URL = "/message-count";
  constexpr static const char *VIEW_URL = "/view";

 public:
  /**
   * @brief setHostPort устанавливает порт к которому отправляется запрос
   * @param hostPort порт к которому отправляется запрос
   */
  void setHostPort(unsigned short hostPort) noexcept { _hostPort = hostPort; }

  template <typename T>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest(T &&data){
      throw std::logic_error(std::string("Data type not supported: ") + typeid(data).name());
  }

  /**
   * @brief generatePostRandomStringRequest генерирует POST запрос
   * строки
   * @return пару из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QString>(QString &&string) {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + STRING_URL);
    QNetworkRequest request(url);

    auto body = string.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "plain/text");
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(body.length()));

    return std::make_pair(std::move(request), std::move(body));
  }
  /**
   * @brief generatePostRandomJsonRequest генерирует POST запрос структуры Data в виде json
   * @return пара из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QJsonObject>(QJsonObject &&jsonObj) {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + JSON_URL);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(jsonObj);
    QByteArray byteArrayJson = doc.toJson();
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(byteArrayJson.length()));

    return std::make_pair(std::move(request), std::move(byteArrayJson));
  }

  /**
   * @brief generatePostBinaryRequest генерирует POST запрос содержимого бинарного файла
   * @param binaryFilepath путь к бинарному файлу
   * @return пара из запроса и тела
   */
  template <>
  std::pair<QNetworkRequest, QByteArray> generatePostRequest<QFile>(QFile &&binaryFile) {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + BINARY_URL);
    QNetworkRequest request(url);

    QByteArray body = binaryFile.readAll();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(body.length()));

    return std::make_pair(std::move(request), std::move(body));
  }
  /**
   * @brief getMessageCount генерирует GET запрос на количество сообщений в дб
   * @return запрос
   */
  QNetworkRequest getMessageCount() {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) +
             MESSAGE_COUNT_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    return request;
  }
  /**
   * @brief getView генерирует GET запрос на view
   * @return запрос
   */
  QNetworkRequest getView() {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + VIEW_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);
    return request;
  }

 private:
  unsigned short _hostPort;
};

}  // namespace http
}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
