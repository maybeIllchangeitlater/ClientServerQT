#include "jsonRepository.h"

namespace test{

void JsonRepository::insertJson(const std::string &name, const std::string &id,
                                const std::string &number, const std::string &date,
                                const std::string &time){
    pqxx::work task(_dbConnection);

    std::string sql = "INSERT INTO json_data (name, gen_id, number, created_date, recieved_date) VALUES (" +
                name + ", " + id + ", " + number + ", " + date + ", " + time + ")";
    try{
        task.exec(sql);
        task.commit();
    }catch(const std::exception &e){
        task.abort();
        throw;
    }
}

pqxx::result JsonRepository::getJsonCount(){
    pqxx::work task(_dbConnection);

    std::string sql = "SELECT id FROM json_data ORDER BY id DESCLIMIT 1";
        try {
          auto result = task.exec(sql);
          return result;
        } catch (const std::exception &e) {
          task.abort();
          throw;
        }
}
}
