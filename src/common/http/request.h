#ifndef CLIENTSERVERQT_COMMON_HTTP_REQUEST_H_
#define CLIENTSERVERQT_COMMON_HTTP_REQUEST_H_

#include "../enums/requestMethod.h"
#include "requestString.h"
#include "header.h"
#include <QString>
#include <QByteArray>
#include <QMap>

namespace test {
namespace http {

class Request {
public:
    constexpr static const char * STRING_URL = "/text-data";
    constexpr static const char * JSON_URL = "//structured-data";
    constexpr static const char * BINARY_URL = "/file-upload";
    constexpr static const char * MESSAGE_COUNT_URL = "/message-count";
    /**
     * @brief Request class representing HTTP request
     * @param method HTTP request method (GET, POST, etc.)
     * @param url Request URL
     * @param header HTTP headers
     * @param body Request body
     */
    Request(RequestMethod method, const QString& url, const Header& header, const QByteArray& body)
        : _method(method), _url(url), _header(header), _body(body) {}
    /**
     * @brief Request class representing HTTP request for request without body
     * @param method HTTP request method (GET, POST, etc.)
     * @param headers HTTP headers
     */
    Request(RequestMethod method, const QString& url, const Header& header)
    : _method(method), _url(url), _header(header){}

    /**
     * @brief toByteArray converts HTTP request to QByteArray
     * @return byte array representation of HTTP request
     */
    QByteArray toByteArray() const {
        QByteArray request;
        request += QString("%1 %2 HTTP/1.1\r\n").arg(requestString(_method), _url).toUtf8();
        if (!_header.contentType.isEmpty()) {
            request += QString("Content-Type: %1\r\n").arg(_header.contentType).toUtf8();
        }
        request += QString("Content-Length: %1\r\n\r\n").arg(_header.contentLength).toUtf8();
        request += _body;
        return request;
    }

private:
    RequestMethod _method;
    QString _url;
    Header _header;
    QByteArray _body;
};

} // namespace http
} // namespace test

#endif // CLIENTSERVERQT_COMMON_HTTP_REQUEST_H_
