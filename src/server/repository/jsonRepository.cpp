#include "jsonRepository.h"

namespace test {

void JsonRepository::insertJson(const std::string &name, const std::string &id,
                                const std::string &number,
                                const std::string &date,
                                const std::string &time) {
  pqxx::work task(_dbConnection);

  std::string sql =
      std::string("INSERT INTO ") + database::JSON_TABLE + " (" +
      database::JSON_TABLE_NAME + ", " + database::JSON_TABLE_GEN_ID + ", " +
      database::JSON_TABLE_NUMBER + ", " + database::JSON_TABLE_CREATED_DATE +
      ", " + database::JSON_TABLE_CREATED_TIME + ") VALUES (" +
      task.quote(name) + ", " + task.quote(id) + ", " + task.quote(number) +
      ", " + task.quote(date) + ", " + task.quote(time) + ")";
  try {
    task.exec(sql);
    task.commit();
  } catch (const std::exception &e) {
    task.abort();
    throw;
  }
}

pqxx::result JsonRepository::getJsonCount() {
  pqxx::work task(_dbConnection);

  std::string sql = std::string("SELECT ") + database::ID + " FROM " +
                    database::JSON_TABLE + " ORDER BY id DESC LIMIT 1";
  try {
    auto result = task.exec(sql);
    return result;
  } catch (const std::exception &e) {
    task.abort();
    throw;
  }
}
}  // namespace test
