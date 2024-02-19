#ifndef CLIENTSERVERQT_COMMON_HTTP_REQUESTSTRING_H_
#define CLIENTSERVERQT_COMMON_HTTP_REQUESTSTRING_H_

#include <QString>
#include "../enums/requestMethod.h"

namespace test{
namespace http{

inline QString requestString(RequestMethod requestMethod) {
        if(requestMethod == GET){
            return "GET";
        }else if(requestMethod == POST){
            return "POST";
        }
        throw std::logic_error("unexpected request method");
    }
} //http
} //test

#endif // CLIENTSERVERQT_COMMON_HTTP_REQUESTSTRING_H_
