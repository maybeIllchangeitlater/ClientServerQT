#ifndef CLIENTSERVERQT_CLIENT_VIEW_BINARYVIEWPOPUP_H_
#define CLIENTSERVERQT_CLIENT_VIEW_BINARYVIEWPOPUP_H_

#include <QCloseEvent>
#include <QDialog>
#include <QJsonObject>

#include "../../common/constants/jsonNames.h"

namespace Ui {
class BinaryViewPopup;
}

/**
 * @brief The BinaryViewPopup class предоставляющий функциональность
 * всплывающего окна для просмотра даты из бинарных файлов
 */
class BinaryViewPopup : public QDialog {
  Q_OBJECT

 public:
  explicit BinaryViewPopup(QWidget *parent = nullptr);
  ~BinaryViewPopup();
  /**
   * @brief setData установить дату
   * @param data джейсон представления даты
   */
  void setData(const QJsonObject &data);

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  Ui::BinaryViewPopup *ui;
};

#endif  // CLIENTSERVERQT_CLIENT_VIEW_BINARYVIEWPOPUP_H_
