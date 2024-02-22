#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QJsonObject>

#include "client/client.h"
#include "stringGenerationPopup.h"
#include "dataGenerationPopup.h"
#include "viewShowPopup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 public slots:
  void connectToServer();
  void getMessageCount();
 signals:
  void postString(QString string);

 private:
  test::Client _client;
  std::unique_ptr<StringGenerationPopup> _stringGenerationPopup =
      std::make_unique<StringGenerationPopup>();
  std::unique_ptr<DataGenerationPopup> _dataGenerationPopup =
          std::make_unique<DataGenerationPopup>();
  std::unique_ptr<ViewShowPopup> _viewShowPopup =
          std::make_unique<ViewShowPopup>();
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
