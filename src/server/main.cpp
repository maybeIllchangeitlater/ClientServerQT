#include "mainwindow.h"
#include "3rdParty/libpqxx/include/pqxx/pqxx"
#include "repository/stringRepository.h"
#include "repository/jsonRepository.h"
#include "service/stringService.h"
#include "service/jsonService.h"
#include "controller/stringController.h"
#include "controller/jsonController.h"
#include "server/server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pqxx::connection connection(
          "dbname=test user=test password=test host=localhost "
          "port=5432");
    test::StringRepository stringRepository(connection);
    test::JsonRepository jsonRepository(connection);
    test::StringService stringService(stringRepository);
    test::JsonService jsonService(jsonRepository);
    test::StringController stringController(stringService);
    test::JsonController jsonController(jsonService);
    test::Server server(stringController, jsonController);
    MainWindow w(server);
    w.show();
    return a.exec();
}
