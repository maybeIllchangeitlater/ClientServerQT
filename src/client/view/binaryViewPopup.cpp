#include "binaryViewPopup.h"

#include "ui_binaryViewPopup.h"

BinaryViewPopup::BinaryViewPopup(QWidget *parent)
    : QDialog(parent), ui(new Ui::BinaryViewPopup) {
  ui->setupUi(this);
}

BinaryViewPopup::~BinaryViewPopup() { delete ui; }

void BinaryViewPopup::setData(const QJsonObject &json) {
  ui->name->setText(json[test::json::NAME].toString());
  ui->id->setText(json[test::json::ID].toString());
  ui->number->setText(json[test::json::NUMBER].toString());
  ui->dateCreated->setText(json[test::json::DATE].toString());
  ui->timeCreated->setText(json[test::json::TIME].toString());
}

void BinaryViewPopup::closeEvent(QCloseEvent *event) {
  ui->name->clear();
  ui->id->clear();
  ui->number->clear();
  ui->dateCreated->clear();
  ui->timeCreated->clear();
  event->accept();
}
