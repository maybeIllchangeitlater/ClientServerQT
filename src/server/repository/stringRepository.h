#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_

#include <string>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
/**
 * @brief The StringRepository class предоставляющий функциональность для работы с строковой базой данных
 */
class StringRepository{
public:
    /**
     * @brief StringRepository конструктор репозитория хранящего строковую дату
     * @param dbConnection pqxx::connection к базе данных
     */
    explicit StringRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    /**
     * @brief insertString вставка строки в базу данных
     * @param stringToInsert строка для вставки
     */
    void insertString(const std::string& stringToInsert);
    /**
     * @brief getStringCount получение количества строковых сообщений полученных сервером
     * @return результат запроса
     */
    pqxx::result getStringCount();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_STRINGREPOSITORY_H_
