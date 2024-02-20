#include "stringRepository.h"

namespace test{

void StringRepository::insertString(const std::string& stringToInsert){
    pqxx::work task(_dbConnection);

    std::string sql = "INSERT INTO string_data (text) VALUES (" + stringToInsert + ")";
    try{
        task.exec(sql);
        task.commit();
    }catch(const std::exception &e){
        task.abort();
        throw;
    }
}

pqxx::result StringRepository::getStringCount(){
    pqxx::work task(_dbConnection);

    std::string sql = "SELECT id FROM string_data ORDER BY id DESCLIMIT 1";
        try {
          auto result = task.exec(sql);
          return result;
        } catch (const std::exception &e) {
          task.abort();
          throw;
        }
}

}
