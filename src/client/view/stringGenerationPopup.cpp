#include "stringGenerationPopup.h"

#include "ui_stringGenerationPopup.h"

StringGenerationPopup::StringGenerationPopup(QWidget *parent)
    : QDialog(parent), ui(new Ui::StringGenerationPopup) {
  ui->setupUi(this);
  connect(ui->sendButton, &QPushButton::clicked, this,
          [&]() { emit sendString(ui->lineEdit->text()); });
  connect(ui->generateButton, &QPushButton::clicked, this,
          [&]() { emit giveMeString(); });
}

StringGenerationPopup::~StringGenerationPopup() { delete ui; }

void StringGenerationPopup::setString(QString &&string) {
  ui->lineEdit->setText(string);
}

void StringGenerationPopup::closeEvent(QCloseEvent *event) {
  ui->lineEdit->clear();
  event->accept();
}
