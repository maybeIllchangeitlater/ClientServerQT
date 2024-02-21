#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_

#include <QJsonDocument>
#include <QJsonObject>
#include "../service/jsonService.h"
#include "../service/stringService.h"
#include "../service/viewService.h"
#include "../service/binaryService.h"

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
     * @param binaryService объект для обработки бинарных файлов
     * @param viewService объект для обработки view
     */
    explicit Controller(StringService &stringService, JsonService &jsonService,
                        BinaryService &binaryService, ViewService &viewService)
        : _stringService(stringService),
          _jsonService(jsonService),
          _binaryService(binaryService),
          _viewService(viewService)  {}
    /**
     * @brief postString записать строку в репозиторий
     * @param data запрос
     * @return сообщение об ошибке
     */
    QString postString(const QByteArray& data){
        try{
            _stringService.postString(data);
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
            _jsonService.postJson(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }
    /**
     * @brief postBinary записать бинарный файл в репозиторий
     * @param data запрос
     * @return сообщение об ошибке
     */
    QString postBinary(const QByteArray& data) {
        try{
            _binaryService.postBinary(data);
            return "";
        }catch(const std::exception &e){
            return e.what();
        }
    }
    /**
     * @brief getMessageCount получить количество сообщений отправленных серверу за все время
     * @return количество сообщений
     */
    QByteArray getMessageCount(){
        try{
           size_t stringCount = _stringService.getStringCount();
           size_t jsonCount = _jsonService.getJsonCount();
           size_t binaryCount = _binaryService.getBinaryCount();
           return QByteArray::number(stringCount + jsonCount + binaryCount);
        } catch(const std::exception &e) {
            return e.what();
        }
    }
    /**
     * @brief getView получить view из базы данных
     * @return QByteArray репрезентацию view
     */
    QByteArray getView() {
        try{
            return _viewService.getView();
        }catch(const std::exception &e) {
                    return e.what();
        }
    }
    private:
        StringService &_stringService;
        JsonService &_jsonService;
        BinaryService &_binaryService;
        ViewService &_viewService;
};
} //test

#endif //CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
