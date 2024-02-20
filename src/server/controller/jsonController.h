#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_JSONCONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_JSONCONTROLLER_H_

#include "../service/jsonService.h"

namespace test{
class JsonController{
public:
    explicit JsonController(JsonService &jsonService)
        : _jsonService(jsonService) {}

    QString postJson(const QByteArray& data) {
        try{
            _jsonService.PostJson(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }

    QString getJsonCount(){
        try{
           return _jsonService.GetJsonCount();
        } catch(const std::exception &e) {
            return e.what();
        }
    }
    private:
        JsonService &_jsonService;
};
} //test

#endif //CLIENTSERVERQT_SERVER_CONTROLLER_JSONCONTROLLER_H_
