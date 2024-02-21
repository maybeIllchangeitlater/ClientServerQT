#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_

#include "../service/jsonService.h"
#include "../service/stringService.h"

namespace test{
class Controller{
public:
    explicit Controller(StringService &stringService, JsonService &jsonService)
        : _stringService(stringService),
          _jsonService(jsonService) {}

    QString postString(const QByteArray& data){
        try{
            _stringService.PostString(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }

    QString postJson(const QByteArray& data) {
        try{
            _jsonService.PostJson(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }

    QString getMessageCount(){
        try{
           size_t stringCount = _stringService.GetStringCount();
           size_t jsonCount = _jsonService.GetJsonCount();
           return QString::number(stringCount + jsonCount);
        } catch(const std::exception &e) {
            return e.what();
        }
    }
    private:
        StringService &_stringService;
        JsonService &_jsonService;
};
} //test

#endif //CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
