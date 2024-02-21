#ifndef CLIENTSERVERQT_SERVER_REPOSITORY_BINARYREPOSITORY_H_
#define CLIENTSERVERQT_SERVER_REPOSITORY_BINARYREPOSITORY_H_

#include <QByteArray>
#include "../3rdParty/libpqxx/include/pqxx/pqxx"

namespace test{
/**
 * @brief The BinaryRepository class предоставляющий функциональность для работы с базой данных бинарных файлоф
 */
class BinaryRepository{
public:
    /**
     * @brief BinaryRepository конструктор репозитория хранящего бинарную дату
     * @param dbConnection pqxx::connection к базе данных
     */
    explicit BinaryRepository(pqxx::connection &dbConnection)
        : _dbConnection(dbConnection) {}
    /**
     * @brief insertBinary вставка бинарного файла в базу данных
     * @param binaryData бинарный файл в виде QByteArray
     */
    void insertBinary(const QByteArray &binaryData);
    /**
     * @brief getBinaryCount получение количества бинарных файлов полученных сервером
     * @return результат запроса
     */
    pqxx::result getBinaryCount();
private:
    pqxx::connection &_dbConnection;
};

} //test

#endif //CLIENTSERVERQT_SERVER_REPOSITORY_BINARYREPOSITORY_H_
