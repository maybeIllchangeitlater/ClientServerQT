#ifndef CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_

#include "../repository/stringRepository.h"
#include <QString>

namespace test{
/**
 * @brief The StringService class класс предоставляющий функциональность для обработки строковой даты
 */
class StringService{
public:
    /**
     * @brief StringService конструктор принимающий в себя репозиторий
     * @param stringRepository объект класса отвечающий за связь с базой данных
     */
    explicit StringService(StringRepository &stringRepository) : _stringRepository(stringRepository) {}
    /**
     * @brief PostString брабатывает и передает строковые данные в репозиторий
     * @param data POST запрос
     */
    void PostString(const QByteArray& data){
        std::string body(data.mid(data.lastIndexOf("\r\n\r\n")).data() + 4);
            if(!body.empty()){
                _stringRepository.insertString(body);
        }else {
            throw std::logic_error("attempted to post empty string");
        }
    }
    /**
     * @brief GetStringCount получение количества строковых сообщений полученных сервером
     * @return количество сообщений
     */
    size_t GetStringCount() {
        auto result = _stringRepository.getStringCount();
        return result[0]["id"].as<size_t>();
    }

private:
    StringRepository& _stringRepository;
};
}

#endif //CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
