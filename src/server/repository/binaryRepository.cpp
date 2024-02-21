#include "binaryRepository.h"

namespace test{

void BinaryRepository::insertBinary(const QByteArray &binaryData) {
    pqxx::work task(_dbConnection);
    try{
        task.exec_params("INSERT INTO binary_data (data) VALUES ($1)", binaryData.data());
        task.commit();
    }catch(const std::exception &e){
        task.abort();
        throw;
    }
}

pqxx::result BinaryRepository::getBinaryCount() {
    pqxx::work task(_dbConnection);
    std::string sql = "SELECT id FROM binary_data ORDER BY id DESC LIMIT 1";
    try{
        auto result = task.exec(sql);
        return result;
    }catch(const std::exception &e){
        task.abort();
        throw;
    }
}
}
