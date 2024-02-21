#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_

#include "../service/jsonService.h"
#include "../service/stringService.h"

namespace test{
/**
 * @brief The Controller class предоставляющий функциональность для записи и получения данных из базы данных
 */
class Controller{
public:
    /**
     * @brief Controller конструктор принимающий в себя два объекта сервисов
     * @param stringService объект для обработки json даты
     * @param jsonService объект для обработки строковой даты
     */
    explicit Controller(StringService &stringService, JsonService &jsonService)
        : _stringService(stringService),
          _jsonService(jsonService) {}
    /**
     * @brief postString записать строку в репозиторий
     * @param data запрос
     * @return сообщение об ошибке
     */
    QString postString(const QByteArray& data){
        try{
            _stringService.PostString(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }
    /**
     * @brief postJson записать json в репозиторий
     * @param data запрос
     * @return сообщение об ошибке
     */
    QString postJson(const QByteArray& data) {
        try{
            _jsonService.PostJson(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }
    /**
     * @brief getMessageCount получить количество сообщений отправленных серверу за все время
     * @return количество сообщений
     */
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
