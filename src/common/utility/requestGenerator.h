#ifndef CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_

#include "../common/data.h"
#include "dateTime.h"
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QUrl>

namespace test{
namespace http{

class RequestGenerator{
    constexpr static const char * STRING_URL = "/text-data";
    constexpr static const char * JSON_URL = "/structured-data";
    constexpr static const char * BINARY_URL = "/file-upload";
    constexpr static const char * MESSAGE_COUNT_URL = "/message-count";
    constexpr static const char * VIEW_URL = "/view";
public:
    /**
     * @brief setHostPort устанавливает порт к которому отправляется запрос
     * @param hostPort порт к которому отправляется запрос
     */
    void setHostPort(unsigned short hostPort) noexcept{
        _hostPort = hostPort;
    }

    /**
     * @brief generatePostRandomStringRequest генерирует POST запрос случайной строки
     * @return пару из запроса и тела
     */
    std::pair<QNetworkRequest, QByteArray> generatePostRandomStringRequest() {
        QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + STRING_URL);
        QNetworkRequest request(url);

        auto body = _randStringGen.generateNumCharString().toUtf8();

        request.setHeader(QNetworkRequest::ContentTypeHeader, "plain/text");
        request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(body.length()));

        return std::make_pair(std::move(request), std::move(body));

    }
    /**
     * @brief generatePostRandomJsonRequest генерирует POST запрос случайно сгенерированной Data в виде json
     * @return пару из запроса и тела
     */
    std::pair<QNetworkRequest, QByteArray> generatePostRandomJsonRequest() {
        QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + JSON_URL);
        QNetworkRequest request(url);

        Data data(_randStringGen, _dateTimeStamper);
        auto body = data.toJson();

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonDocument doc(body);
        QByteArray byteArrayJson = doc.toJson();
        request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(byteArrayJson.length()));

        return std::make_pair(std::move(request), std::move(byteArrayJson));

    }
    /**
     * @brief getMessageCount генерирует GET запрос на количество сообщений в дб
     * @return запрос
     */
    QNetworkRequest getMessageCount() {
        QUrl url("http://127.0.0.1:" + QString::number(_hostPort) + MESSAGE_COUNT_URL);
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
//    std::pair<QNetworkRequest, QByteArray> PostRandomBinayRequest(const Data& data) {

//    }
private:
    RandomStringGenerator _randStringGen;
    DateTime _dateTimeStamper;
    unsigned short _hostPort;
};

} //http
} //test

#endif //CLIENTSERVERQT_CLIENT_UTILITY_REQUESTGENERATOR_H_
