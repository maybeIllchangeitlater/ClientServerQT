#ifndef CLIENTSERVERQT_SERVER_HTTP_HEADER_H_
#define CLIENTSERVERQT_SERVER_HTTP_HEADER_H_

#include "enums/contentType.h"
#include<QString>

namespace test{
namespace http{



struct Header{
    /**
     * @brief Header creates header for message with no body
     */
    Header() = default;
    /**
     * @brief Header creates http header
     * @param contentTyp content type that will be passed
     * @param contentLen content length (body size)
     */
    Header(ContentType contentTyp, size_t contentLen) : contentLength(contentLen) {
        if(contentTyp == PLAIN_TEXT){
            contentType = "text/plain";
        }else if(contentTyp == APPLICATION_JSON){
            contentType = "application/json";
        }else if(contentTyp == APPLICATION_OCTETSTREAM){
            contentType = "application/octet-stream";
        }
    }
    QString contentType;
    size_t contentLength;
};

} //http

} //test

#endif //CLIENTSERVERQT_SERVER_HTTP_HEADER_H_
