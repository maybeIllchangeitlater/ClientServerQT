#ifndef CLIENTSERVERQT_COMMON_CONSTANTS_URI_H_
#define CLIENTSERVERQT_COMMON_CONSTANTS_URI_H_

namespace test{
namespace http{
namespace uri{

constexpr static const char *STRING = "/text-data";
constexpr static const char *JSON = "/structured-data";
constexpr static const char *BINARY = "/file-upload";
constexpr static const char *MESSAGE_COUNT = "/message-count";
constexpr static const char *VIEW = "/view";
constexpr static const char *CLOSE_CONNECTION = "/close";

} //uri
} //http
} //test

#endif //CLIENTSERVERQT_COMMON_CONSTANTS_URI_H_
