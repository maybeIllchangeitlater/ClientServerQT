#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QString projectDir = QCoreApplication::applicationDirPath();
  MainWindow w(projectDir);
  w.show();
  return a.exec();
}
