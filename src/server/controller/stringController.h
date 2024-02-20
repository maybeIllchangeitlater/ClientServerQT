#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_STRINGCONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_STRINGCONTROLLER_H_

#include "../service/stringService.h"

namespace test{
class StringController{
public:
    explicit StringController(StringService &stringService)
        : _stringService(stringService) {}

    QString postString(const QByteArray& data) {
        try{
            _stringService.PostString(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }

    QString getStringCount(){
        try{
           return _stringService.GetStringCount();
        } catch(const std::exception &e) {
            return e.what();
        }
    }
    private:
        StringService &_stringService;
};
} //test

#endif //CLIENTSERVERQT_SERVER_CONTROLLER_STRINGCONTROLLER_H_
