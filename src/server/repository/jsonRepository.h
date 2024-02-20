#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_

#include<string>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
class JsonRepository{
public:
    explicit JsonRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    void insertJson(const std::string &name, const std::string &id,
                    const std::string &number, const std::string &date,
                    const std::string &time);
    pqxx::result getJsonCount();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_
