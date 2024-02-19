#ifndef CLIENTSERVERQT_SERVER_HTTP_STATUSMESSAGE_H_
#define CLIENTSERVERQT_SERVER_HTTP_STATUSMESSAGE_H_

#include<QString>
#include<QMap>
#include "../enums/statusCode.h"

namespace test{
namespace http{

inline QString statusMessage(StatusCode statusCode) {
    static QMap<StatusCode, QString> messages = {
        {OK, "OK"},
        {BAD_REQUEST, "Bad Request"},
    };
    return messages.value(statusCode);
}


}
}

#endif //CLIENTSERVERQT_SERVER_HTTP_STATUSMESSAGE_H_
