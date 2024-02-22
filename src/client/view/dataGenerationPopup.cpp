#include "dataGenerationPopup.h"

#include "ui_dataGenerationPopup.h"

DataGenerationPopup::DataGenerationPopup(QWidget *parent)
    : QDialog(parent), ui(new Ui::DataGenerationPopup) {
  ui->setupUi(this);

  connect(ui->sendButton, &QPushButton::clicked, this,
          [&]() { emit sendData(packToJson()); });
  connect(ui->generateButton, &QPushButton::clicked, this,
          [&]() { emit giveMeData(); });
}

DataGenerationPopup::~DataGenerationPopup() { delete ui; }

QJsonObject DataGenerationPopup::packToJson() {
  QJsonObject json;
  json[test::json::NAME] = ui->name->text();
  json[test::json::ID] = ui->id->text();
  json[test::json::NUMBER] = ui->number->text();
  auto [date, time] = test::DateTime::getDateTime();
  json[test::json::DATE] = date;
  json[test::json::TIME] = time;
  return json;
}

void DataGenerationPopup::setData(const QJsonObject &json) {
  ui->name->setText(json[test::json::NAME].toString());
  ui->id->setText(json[test::json::ID].toString());
  ui->number->setText(json[test::json::NUMBER].toString());
}

void DataGenerationPopup::closeEvent(QCloseEvent *event) {
  ui->name->clear();
  ui->id->clear();
  ui->number->clear();
  event->accept();
}
