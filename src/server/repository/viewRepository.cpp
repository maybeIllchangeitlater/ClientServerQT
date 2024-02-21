#include "viewRepository.h"

namespace test{
    pqxx::result ViewRepository::getCustomView(){
        pqxx::work task(_dbConnection);
        std::string sql("SELECT * FROM custom_view");
        try{
            auto result = task.exec(sql);
            return result;
        }catch(const std::exception &e){
            task.abort();
            throw;
        }
    }
}
