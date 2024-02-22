#ifndef CLIENTSERVERQT_CLIENT_VIEW_MAINWINDOW_H_
#define CLIENTSERVERQT_CLIENT_VIEW_MAINWINDOW_H_

#include <QFileDialog>
#include <QJsonObject>
#include <QMainWindow>
#include <memory>

#include "../../common/data.h"
#include "binaryViewPopup.h"
#include "client/client.h"
#include "dataGenerationPopup.h"
#include "stringGenerationPopup.h"
#include "viewShowPopup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/**
 * @brief The MainWindow class предоставляющий функционал главного окна
 * клиентского приложения для работы с сервером
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QString &projectDir, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  /**
   * @brief connectPopUpsRequested подключает кнопки к всплывающим окнам
   */
  void connectPopUpsRequested();
  /**
   * @brief connectPopUpsFunctionallity подключает функционал всплываюших окон
   */
  void connectPopUpsFunctionallity();
  /**
   * @brief connectNoPopButtons подключает остальные кнопки
   */
  void connectNoPopButtons();

 private:
  test::Client _client;
  std::unique_ptr<StringGenerationPopup> _stringGenerationPopup =
      std::make_unique<StringGenerationPopup>();
  std::unique_ptr<DataGenerationPopup> _dataGenerationPopup =
      std::make_unique<DataGenerationPopup>();
  std::unique_ptr<ViewShowPopup> _viewShowPopup =
      std::make_unique<ViewShowPopup>();
  std::unique_ptr<BinaryViewPopup> _binaryViewPopup =
      std::make_unique<BinaryViewPopup>();
  Ui::MainWindow *ui;
};
#endif  // CLIENTSERVERQT_CLIENT_VIEW_MAINWINDOW_H_
