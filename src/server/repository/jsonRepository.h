#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_

#include<string>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
/**
 * @brief The JsonRepository class предоставляющий функциональность для работы с json базой данных
 */
class JsonRepository{
public:
    /**
     * @brief JsonRepository конструктор репозитория хранящего json дату
     * @param dbConnection pqxx::connection к базе данных
     */
    explicit JsonRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    /**
     * @brief insertJson вставка json в базу данных
     * @param name поле json
     * @param id поле json
     * @param number поле json
     * @param date поле json
     * @param time поле json
     */
    void insertJson(const std::string &name, const std::string &id,
                    const std::string &number, const std::string &date,
                    const std::string &time);
    /**
     * @brief getJsonCount получение количества json сообщений полученных сервером
     * @return результат запроса
     */
    pqxx::result getJsonCount();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_JSONREPOSITORY_H_
