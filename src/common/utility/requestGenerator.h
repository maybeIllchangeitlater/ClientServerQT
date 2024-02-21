#ifndef CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_

#include <QJsonDocument>
#include <QNetworkRequest>
#include <QUrl>

#include "../common/data.h"
#include "dateTime.h"

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

  /**
   * @brief generatePostRandomStringRequest генерирует POST запрос случайной
   * строки
   * @return пару из запроса и тела
   */
  std::pair<QNetworkRequest, QByteArray> generatePostRandomStringRequest() {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + STRING_URL);
    QNetworkRequest request(url);

    auto body = _randStringGen.generateNumCharString().toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "plain/text");
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(body.length()));

    return std::make_pair(std::move(request), std::move(body));
  }
  /**
   * @brief generatePostRandomJsonRequest генерирует POST запрос случайно
   * сгенерированной Data в виде json
   * @return картеж из запроса, тела и даты
   */
  std::tuple<QNetworkRequest, QByteArray, Data>
  generatePostRandomJsonRequest() {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + JSON_URL);
    QNetworkRequest request(url);

    Data data(_randStringGen, _dateTimeStamper);
    auto body = data.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(body);
    QByteArray byteArrayJson = doc.toJson();
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(byteArrayJson.length()));

    return std::make_tuple(std::move(request), std::move(byteArrayJson),
                           std::move(data));
  }

  /**
   * @brief generatePostBinaryRequest генерирует POST запрос содержимого бинарного файла
   * @param binaryFilepath путь к бинарному файлу
   * @return пара из запроса и тела
   */
  std::pair<QNetworkRequest, QByteArray> generatePostBinaryRequest(
      const QString &binaryFilepath) {
    QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + BINARY_URL);
    QNetworkRequest request(url);

    QFile file(binaryFilepath);
    if (!file.open(QIODevice::ReadOnly)) {
      throw std::runtime_error("failed to open file: " +
                               binaryFilepath.toStdString());
    }
    QByteArray body = file.readAll();

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
  //    std::pair<QNetworkRequest, QByteArray> PostRandomBinayRequest(const
  //    Data& data) {

  //    }
 private:
  RandomStringGenerator _randStringGen;
  DateTime _dateTimeStamper;
  unsigned short _hostPort;
};

}  // namespace http
}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
