#ifndef CLIENTSERVERQT_CLIENT_VIEW_DATAGENERATIONPOPUP_H_
#define CLIENTSERVERQT_CLIENT_VIEW_DATAGENERATIONPOPUP_H_

#include <QCloseEvent>
#include <QDialog>
#include <QJsonObject>

#include "../../common/constants/jsonNames.h"
#include "../../common/dateTime.h"

namespace Ui {

class DataGenerationPopup;
}
/**
 * @brief DataGenerationPopup class  предоставляющий функциональность всплывающего окна для отправки/генерации даты
 */
class DataGenerationPopup : public QDialog {
  Q_OBJECT

 public:
  explicit DataGenerationPopup(QWidget *parent = nullptr);
  ~DataGenerationPopup();
    /**
   * @brief setData установить дату
   * @param data джейсон представления даты
   */
  void setData(const QJsonObject &data);

 signals:
  /**
   * @brief sendData отправить дату на сервер
   */
  void sendData(QJsonObject);
  /**
   * @brief giveMeData получить случайно сгенерированную дату
   */
  void giveMeData();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  QJsonObject packToJson();
  Ui::DataGenerationPopup *ui;
};

#endif  // CLIENTSERVERQT_CLIENT_VIEW_DATAGENERATIONPOPUP_H_
