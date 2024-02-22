#ifndef CLIENTSERVERQT_CLIENT_VIEW_STRINGGENERATIONPOPUP_H_
#define CLIENTSERVERQT_CLIENT_VIEW_STRINGGENERATIONPOPUP_H_

#include <QCloseEvent>
#include <QDialog>

namespace Ui {

class StringGenerationPopup;
}
/**
 * @brief StringGenerationPopup class предоставляющий функциональность
 * всплывающего окна для отправки/генерации строк
 */
class StringGenerationPopup : public QDialog {
  Q_OBJECT

 public:
  explicit StringGenerationPopup(QWidget *parent = nullptr);
  ~StringGenerationPopup();
  /**
   * @brief setString установить строку
   * @param string строка
   */
  void setString(QString &&string);

 signals:
  /**
   * @brief sendString отправить строку на сервер
   */
  void sendString(QString);
  /**
   * @brief giveMeString получить случайно сгенерированную строку
   */
  void giveMeString();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  Ui::StringGenerationPopup *ui;
};

#endif  // CLIENTSERVERQT_CLIENT_VIEW_STRINGGENERATIONPOPUP_H_
