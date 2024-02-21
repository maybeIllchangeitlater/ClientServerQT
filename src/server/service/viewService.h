#ifndef CLIENTSERVERQT_SERVER_SERVICE_VIEWSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_VIEWSERVICE_H_

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"
#include "../repository/viewRepository.h"
#include "../common/constants/BDNames.h"

namespace test {
/**
 * @brief The ViewService class предоставляющий функциональность для обработки
 * view
 */
class ViewService {
 public:
  /**
   * @brief ViewService конструктор принимающий в себя репозиторий
   * @param viewRepository объект класса отвечающий за связь с базой данных
   */
  explicit ViewService(ViewRepository& viewRepository)
      : _viewRepository(viewRepository) {}

    /**
   * @brief getView получить view из базы данных
   * @return QByteArray с полями view
   */
  QByteArray getView() {
    pqxx::result result = _viewRepository.getCustomView();
    QJsonArray jsonArray;

    for (const auto& row : result) {
      QJsonObject rowObject;
      rowObject[database::CUSTOM_VIEW_ID] = row[0].as<int>();
      rowObject[database::CUSTOM_VIEW_TEXTNAME] = QString::fromStdString(row[1].as<std::string>());
      rowObject[database::CUSTOM_VIEW_RECIEVED_DATE] =
          QString::fromStdString(row[2].as<std::string>());
      jsonArray.append(rowObject);
    }
    return QJsonDocument(jsonArray).toJson();
  }

 private:
  ViewRepository& _viewRepository;
};
}  // namespace test

#endif  // CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
