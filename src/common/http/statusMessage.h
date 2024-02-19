#ifndef CLIENTSERVERQT_COMMON_HTTP_STATUSMESSAGE_H_
#define CLIENTSERVERQT_COMMON_HTTP_STATUSMESSAGE_H_

#include<QString>
#include<QMap>
#include "../enums/statusCode.h"

namespace test{
namespace http{

inline QString statusMessage(StatusCode statusCode) {
    if(statusCode == OK){
        return "OK";
    }else if(statusCode == BAD_REQUEST){
        return "BAD REQUEST";
    }
    throw std::logic_error("unexpected status");
}


}
}

#endif //CLIENTSERVERQT_COMMON_HTTP_STATUSMESSAGE_H_
