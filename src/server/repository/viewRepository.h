#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_VIEWREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_VIEWREPOSITORY_H_

#include <string>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
/**
 * @brief The ViewRepository class предоставляющий функциональность для работы с view из базы данных
 */
class ViewRepository{
public:
    /**
     * @brief ViewRepository конструктор репозитория для работы с view
     * @param dbConnection pqxx::connection к базе данных
     */
    explicit ViewRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    /**
     * @brief getCustomView получает custom_view из базы данных
     * @return результат запроса
     */
    pqxx::result getCustomView();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_VIEWREPOSITORY_H_
