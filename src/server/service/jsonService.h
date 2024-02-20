#ifndef CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_

#include "../repository/jsonRepository.h"
#include "../common/data.h"
#include <QString>
#include <QJsonDocument>

namespace test{
class JsonService{
public:
    explicit JsonService(JsonRepository &jsonRepository) : _jsonRepository(jsonRepository) {}

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

    QString GetJsonCount() {
        auto result = _jsonRepository.getJsonCount();
        return QString::number(result[0]["id"].as<unsigned long>());
    }

private:
    JsonRepository& _jsonRepository;
};
}

#endif //CLIENTSERVERQT_SERVER_SERVICE_JSONSERVICE_H_
