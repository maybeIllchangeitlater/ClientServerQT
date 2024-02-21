#ifndef CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_

#include "../repository/jsonRepository.h"
#include "../common/data.h"
#include <QString>
#include <QJsonDocument>

namespace test{
/**
 * @brief The JsonService class предоставляющий функциональность для обработки json даты
 */
class JsonService{
public:
    /**
     * @brief JsonService конструктор принимающий в себя репозиторий
     * @param jsonRepository объект класса отвечающий за связь с базой данных
     */
    explicit JsonService(JsonRepository &jsonRepository) : _jsonRepository(jsonRepository) {}
    /**
     * @brief PostJson обрабатывает и передает json данные в репозиторий
     * @param data Post запрос
     */
    void PostJson(const QByteArray& data){
        auto body = data.mid(data.lastIndexOf("\r\n\r\n") + 4);
        QJsonDocument jsonDocument = QJsonDocument::fromJson(body);
        if(!jsonDocument.isNull()) {
            QJsonObject jsonObject = jsonDocument.object();
            Data jsonData(jsonObject);
            _jsonRepository.insertJson(jsonData.GetName().toStdString(),
                                       jsonData.GetId().toStdString(),
                                       jsonData.GetNumber().toStdString(),
                                       jsonData.GetDate().toStdString(),
                                       jsonData.GetTime().toStdString());
        }else {
            throw std::logic_error("attempted to post invalid json");
        }
    }
    /**
     * @brief GetJsonCount получение количества json сообщений полученных сервером
     * @return количество сообщений
     */
    size_t GetJsonCount() {
        auto result = _jsonRepository.getJsonCount();
        return result[0]["id"].as<size_t>();
    }

private:
    JsonRepository& _jsonRepository;
};
}

#endif //CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_
