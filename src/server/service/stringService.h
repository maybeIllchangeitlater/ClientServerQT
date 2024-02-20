#ifndef CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_

#include "../repository/stringRepository.h"
#include <QString>

namespace test{
class StringService{
public:
    explicit StringService(StringRepository &stringRepository) : _stringRepository(stringRepository) {}

    void PostString(const QByteArray& data){
        std::string body(data.mid(data.lastIndexOf("\r\n\r\n")).data() + 4);
            if(!body.empty()){
                _stringRepository.insertString(body);
        }else {
            throw std::logic_error("attempted to post empty string");
        }
    }

    QString GetStringCount() {
        auto result = _stringRepository.getStringCount();
        return QString::number(result[0]["id"].as<unsigned long>());
    }

private:
    StringRepository& _stringRepository;
};
}

#endif //CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
