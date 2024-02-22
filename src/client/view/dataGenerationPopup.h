#ifndef DATAGENERATIONPOPUP_H
#define DATAGENERATIONPOPUP_H

#include <QCloseEvent>
#include <QDialog>
#include <QJsonObject>

#include "../../common/constants/jsonNames.h"
#include "../../common/dateTime.h"

namespace Ui {
class DataGenerationPopup;
}

class DataGenerationPopup : public QDialog {
  Q_OBJECT

 public:
  explicit DataGenerationPopup(QWidget *parent = nullptr);
  ~DataGenerationPopup();

  void setData(const QJsonObject &data);

 signals:
  void sendData(QJsonObject);
  void giveMeData();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  QJsonObject packToJson();
  Ui::DataGenerationPopup *ui;
};

#endif  // DATAGENERATIONPOPUP_H
