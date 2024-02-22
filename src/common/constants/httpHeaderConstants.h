#ifndef CLIENTSERVERQT_COMMON_CONSTANTS_HTTPHEADERCONSTANTS_H_
#define CLIENTSERVERQT_COMMON_CONSTANTS_HTTPHEADERCONSTANTS_H_

namespace test{
namespace http{
namespace headers{

constexpr static const char * CONNECTION_HEADER = "Connection";
constexpr static const char * CONTENT_LENGTH_HEADER = "Content-Length: ";
constexpr static const char * CONTENT_TYPE_HEADER = "Content-Type: ";
constexpr static const char * CONNECTION_STATUS_ALIVE = "keep-alive";
constexpr static const char * CONNECTION_STATUS_CLOSE = "close";
constexpr static const char * PLAIN_TEXT = "text/plain";
constexpr static const char * APPLICATION_JSON = "application/json";
constexpr static const char * APPLICATION_OCTETSTREAM = "application/octet-stream";

constexpr static const char * HEADER_OK = "HTTP/1.1 200 OK\r\n";
constexpr static const char * HEADER_BAD_REQUEST = "HTTP/1.1 400 BAD REQUEST\r\n";
constexpr static const char * HEADER_DELIMITER = "\r\n";
constexpr static const char * HEADERS_END = "\r\n\r\n";


}//headers
}//http
}//test

#endif //CLIENTSERVERQT_COMMON_CONSTANTS_HTTPHEADERCONSTANTS_H_
