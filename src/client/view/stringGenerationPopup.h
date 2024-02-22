#ifndef STRINGGENERATIONPOPUP_H
#define STRINGGENERATIONPOPUP_H

#include <QCloseEvent>
#include <QDialog>

namespace Ui {
class StringGenerationPopup;
}

class StringGenerationPopup : public QDialog {
  Q_OBJECT

 public:
  explicit StringGenerationPopup(QWidget *parent = nullptr);
  ~StringGenerationPopup();

  void setString(QString &&string);

 signals:
  void sendString(QString);
  void giveMeString();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private:
  Ui::StringGenerationPopup *ui;
};

#endif  // STRINGGENERATIONPOPUP_H
