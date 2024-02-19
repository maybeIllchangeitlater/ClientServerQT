#ifndef CLIENTSERVERQT_COMMON_HTTP_RESPONSE_H_
#define CLIENTSERVERQT_COMMON_HTTP_RESPONSE_H_

#include "../enums/statusCode.h"
#include "header.h"
#include "statusMessage.h"
#include <QString>
#include <QMap>

namespace test{
namespace http{
class Response {
public:
    /**
     * @brief Response class representing HTTP response
     * @param statusCode response status code
     * @param statusMessage human readable status message corresponding to status code
     * @param headers HTTP headers
     * @param body message
     */
    Response(StatusCode statusCode, const Header& header, const QByteArray& body)
        : _statusCode(statusCode), _header(header), _body(body) {}

    /**
     * @brief Response class representing HTTP response for response without body
     * @param statusCode response status code
     * @param statusMessage human readable status message corresponding to status code
     * @param headers HTTP headers
     */
    Response(StatusCode statusCode, const Header& header)
        : _statusCode(statusCode), _header(header){}

    /**
     * @brief toByteArray converts HTTP response to QByteArray
     * @return byte array reporesentation of HTTP response
     */
    QByteArray toByteArray() const {
        QByteArray response;
        response += QString("HTTP/1.1 %1 %2\r\n").arg(_statusCode).arg(statusMessage(_statusCode)).toUtf8();
        if(!_header.contentType.isEmpty()){
            response += QString("Content-Type: %1\r\n").arg(_header.contentType).toUtf8();
        }
        response += QString("Content-Length: %1\r\n\r\n").arg(_header.contentLength).toUtf8();
        response += _body;
        return response;
    }

private:
    StatusCode _statusCode;
    Header _header;
    QByteArray _body;
};

}//http
}//test


#endif //CLIENTSERVERQT_COMMON_HTTP_RESPONSE_H_
