#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_

#include <string>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
class StringRepository{
public:
    explicit StringRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    void insertString(const std::string& stringToInsert);
    pqxx::result getStringCount();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_
