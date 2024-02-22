#include "binaryRepository.h"

namespace test {

void BinaryRepository::insertBinary(const QByteArray &binaryData) {
  pqxx::work task(_dbConnection);
  try {
    task.exec_params(std::string("INSERT INTO ") + database::BINARY_TABLE +
                         " (" + database::BINARY_TABLE_DATA + ") VALUES ($1)",
                     binaryData.data());
    task.commit();
  } catch (const std::exception &e) {
    task.abort();
    throw;
  }
}

pqxx::result BinaryRepository::getBinaryCount() {
  pqxx::work task(_dbConnection);
  std::string sql = std::string("SELECT ") + database::ID + " FROM " +
                    database::BINARY_TABLE + " ORDER BY id DESC LIMIT 1";
  try {
    auto result = task.exec(sql);
    return result;
  } catch (const std::exception &e) {
    task.abort();
    throw;
  }
}
}  // namespace test
