#include "3rdParty/libpqxx/include/pqxx/pqxx"
#include "repository/stringRepository.h"
#include "repository/jsonRepository.h"
#include "repository/binaryRepository.h"
#include "repository/viewRepository.h"
#include "service/stringService.h"
#include "service/jsonService.h"
#include "service/binaryService.h"
#include "service/viewService.h"
#include "controller/controller.h"
#include "server/server.h"
#include "config/config.h"
#include <QHostInfo>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto config = test::Config::fromJsonFile("../config.json");
    pqxx::connection connection(config.DBSettingsString().toStdString());
    test::StringRepository stringRepository(connection);
    test::JsonRepository jsonRepository(connection);
    test::BinaryRepository binaryRepository(connection);
    test::ViewRepository viewRepository(connection);
    test::StringService stringService(stringRepository);
    test::JsonService jsonService(jsonRepository);
    test::BinaryService binaryService(binaryRepository);
    test::ViewService viewService(viewRepository);
    test::Controller controller(stringService, jsonService, binaryService, viewService);
    test::Server server(controller);


    server.listen(QHostAddress(config.serverHost), config.serverPort);
    return a.exec();
}
