#include "stringRepository.h"

namespace test{

void StringRepository::insertString(const std::string& stringToInsert){
    pqxx::work task(_dbConnection);

    std::string sql = std::string("INSERT INTO ") + database::STRING_TABLE +" (" + database::STRING_TABLE_TEXT
            + ") VALUES (" + task.quote(stringToInsert) + ")";
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

    std::string sql = std::string("SELECT ") + database::ID + " FROM " + database::STRING_TABLE + " ORDER BY id DESC LIMIT 1";
        try {
          auto result = task.exec(sql);
          return result;
        } catch (const std::exception &e) {
          task.abort();
          throw;
        }
}

}
