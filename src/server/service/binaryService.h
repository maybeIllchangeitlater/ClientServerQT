#ifndef CLIENTSERVERQT_SERVER_SERVICE_BINARYSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_BINARYSERVICE_H_

#include <QJsonDocument>
#include <QString>
#include <QDebug>

#include "../3rdParty/libpqxx/include/pqxx/pqxx"
#include "../repository/binaryRepository.h"
#include "../common/constants/httpHeaderConstants.h"
#include "../common/constants/BDNames.h"


namespace test {
/**
 * @brief The BinaryService class предоставляющий функциональность для обработки
 * бинарной даты
 */
class BinaryService {
 public:
  /**
   * @brief BinaryService конструктор принимающий в себя репозиторий
   * @param BinaryRepository объект класса отвечающий за связь с базой данных
   */
  explicit BinaryService(BinaryRepository& binaryRepository)
      : _binaryRepository(binaryRepository) {}
  /**
   * @brief postBinary обрабатывает и передает бинарные данные в репозиторий
   * @param data Post запрос
   */
  void postBinary(const QByteArray& data) {
     QByteArray body(data.mid(data.indexOf(http::headers::HEADERS_END) + 4));
     qDebug() << body.data();
     if (!body.isEmpty()){
         _binaryRepository.insertBinary(body);
     } else {
         throw std::logic_error("attempted to post empty binary");
     }
  }
  /**
   * @brief getBinaryCount получение количества бинарных файлов полученных сервером
   * @return количество файлов
   */
  size_t getBinaryCount() {
      auto result = _binaryRepository.getBinaryCount();
      return result.empty() ? 0 : result[0][database::ID].as<size_t>();
  }

 private:
  BinaryRepository& _binaryRepository;
};
}  // namespace test

#endif  // CLIENTSERVERQT_SERVER_SERVICE_BINARYSERVICE_H_
