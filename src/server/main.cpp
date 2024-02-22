#include <QCoreApplication>
#include <QHostInfo>

#include "3rdParty/libpqxx/include/pqxx/pqxx"
#include "config/config.h"
#include "controller/controller.h"
#include "repository/binaryRepository.h"
#include "repository/jsonRepository.h"
#include "repository/stringRepository.h"
#include "repository/viewRepository.h"
#include "server/server.h"
#include "service/binaryService.h"
#include "service/jsonService.h"
#include "service/stringService.h"
#include "service/viewService.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  auto config = test::Config::fromJsonFile("../src/config.json");
  pqxx::connection connection(config.DBSettingsString().toStdString());
  test::StringRepository stringRepository(connection);
  test::JsonRepository jsonRepository(connection);
  test::BinaryRepository binaryRepository(connection);
  test::ViewRepository viewRepository(connection);
  test::StringService stringService(stringRepository);
  test::JsonService jsonService(jsonRepository);
  test::BinaryService binaryService(binaryRepository);
  test::ViewService viewService(viewRepository);
  test::Controller controller(stringService, jsonService, binaryService,
                              viewService);
  QString projectDir = QCoreApplication::applicationDirPath();
  test::Server server(controller, projectDir);

  server.listen(QHostAddress(config.serverHost), config.serverPort);
  return a.exec();
}
