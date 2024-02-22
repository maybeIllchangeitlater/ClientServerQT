#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _client() {
  ui->setupUi(this);

  connect(ui->connectButton, &QPushButton::clicked, this,
          &MainWindow::connectToServer);
  connect(ui->getMessageCount, &QPushButton::clicked, this,
          &MainWindow::getMessageCount);
  connect(&_client, &test::Client::messageCount, this,
          [this](QString count) { ui->responseLabel->setText(count); });
  connect(
      &_client, &test::Client::postedByClient, this,
      [this](QString postStatus) { ui->responseLabel->setText(postStatus); });


  connect(ui->sendString, &QPushButton::clicked, this,
          [&]() { _stringGenerationPopup->exec(); });
  connect(_stringGenerationPopup.get(), &StringGenerationPopup::giveMeString,
          this, [&]() {
            _stringGenerationPopup->setString(_client.generateRandomString());
          });
  connect(_stringGenerationPopup.get(), &StringGenerationPopup::sendString,
          this, [&](QString string) {
            _client.post(std::move(string),
                         &test::Client::handlePostReplyFinished);
          });

  connect(ui->sendData, &QPushButton::clicked, this,
          [&](){_dataGenerationPopup->exec(); });
  connect(_dataGenerationPopup.get(), &DataGenerationPopup::sendData, this, [&](QJsonObject json) {
        _client.post(std::move(json), &test::Client::handlePostReplyFinished);
  });
  connect(_dataGenerationPopup.get(), &DataGenerationPopup::giveMeData, this, [&]() {
      QJsonObject json;
      json[test::json::ID] = _client.generateRandomString();
      json[test::json::NAME] = _client.generateRandomString();
      json[test::json::NUMBER] = _client.generateRandomString();
      _dataGenerationPopup->setData(json);
  });

  connect(ui->getView, &QPushButton::clicked, this, [&](){
      _client.getView();
  });
  connect(&_client, &test::Client::viewRecieved, this, [&](QByteArray view){
      _viewShowPopup->setView(view);
      _viewShowPopup->exec();
  });


}

void MainWindow::connectToServer() {
  _client.connectToServer(ui->linePort->text().toUShort(),
                          ui->lineHost->text());
}

void MainWindow::getMessageCount() { _client.getMessageCount(); }

MainWindow::~MainWindow() { delete ui; }
