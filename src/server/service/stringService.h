#ifndef CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
#define CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_

#include <QString>

#include "../3rdParty/libpqxx/include/pqxx/pqxx"
#include "../repository/stringRepository.h"
#include "../common/constants/httpHeaderConstants.h"
#include "../common/constants/BDNames.h"

namespace test {
/**
 * @brief The StringService class предоставляющий функциональность для обработки
 * строковой даты
 */
class StringService {
 public:
  /**
   * @brief StringService конструктор принимающий в себя репозиторий
   * @param stringRepository объект класса отвечающий за связь с базой данных
   */
  explicit StringService(StringRepository& stringRepository)
      : _stringRepository(stringRepository) {}
  /**
   * @brief postString брабатывает и передает строковые данные в репозиторий
   * @param data POST запрос
   */
  void postString(const QByteArray& data) {
    std::string body(data.mid(data.lastIndexOf(http::headers::HEADERS_END) + 4));
    if (!body.empty()) {
      _stringRepository.insertString(body);
    } else {
      throw std::logic_error("attempted to post empty string");
    }
  }
  /**
   * @brief getStringCount получение количества строковых сообщений полученных
   * сервером
   * @return количество сообщений
   */
  size_t getStringCount() {
    pqxx::result result = _stringRepository.getStringCount();
    return result.empty() ? 0 : result[0][database::ID].as<size_t>();
  }

 private:
  StringRepository& _stringRepository;
};
}  // namespace test

#endif  // CLIENTSERVERQT_SERVER_SERVICE_STRINGSERVICE_H_
