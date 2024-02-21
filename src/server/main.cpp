#include "mainwindow.h"
#include "3rdParty/libpqxx/include/pqxx/pqxx"
#include "repository/stringRepository.h"
#include "repository/jsonRepository.h"
#include "repository/viewRepository.h"
#include "service/stringService.h"
#include "service/jsonService.h"
#include "service/viewService.h"
#include "controller/controller.h"
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
    test::ViewRepository viewRepository(connection);
    test::StringService stringService(stringRepository);
    test::JsonService jsonService(jsonRepository);
    test::ViewService viewService(viewRepository);
    test::Controller controller(stringService, jsonService, viewService);
    test::Server server(controller);
    MainWindow w(server);
    w.show();
    return a.exec();
}
