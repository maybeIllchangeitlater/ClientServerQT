#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QString &projectDir, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _client(projectDir) {
  ui->setupUi(this);

  connectNoPopButtons();
  connectPopUpsRequested();
  connectPopUpsFunctionallity();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::connectPopUpsRequested() {
  connect(ui->sendString, &QPushButton::clicked, this,
          [&]() { _stringGenerationPopup->exec(); });

  connect(&_client, &test::Client::viewRecieved, this, [&](QByteArray view) {
    _viewShowPopup->setView(view);
    _viewShowPopup->exec();
  });

  connect(ui->sendData, &QPushButton::clicked, this,
          [&]() { _dataGenerationPopup->exec(); });

  connect(ui->viewBinaryFile, &QPushButton::clicked, this, [&]() {
    QString filename(QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(),
                                                  "bin files (*.bin)"));
    if(!filename.isEmpty()){
        _binaryViewPopup->setData(test::Data(filename).toJson());
        _binaryViewPopup->exec();
    }
  });
}

void MainWindow::connectPopUpsFunctionallity() {
  connect(_stringGenerationPopup.get(), &StringGenerationPopup::giveMeString,
          this, [&]() {
            _stringGenerationPopup->setString(_client.generateRandomString());
          });
  connect(_stringGenerationPopup.get(), &StringGenerationPopup::sendString,
          this, [&](QString string) {
            _client.post(std::move(string),
                         &test::Client::handlePostReplyFinished);
          });

  connect(_dataGenerationPopup.get(), &DataGenerationPopup::sendData, this,
          [&](QJsonObject json) {
            _client.post(std::move(json),
                         &test::Client::handlePostReplyFinished);
          });
  connect(_dataGenerationPopup.get(), &DataGenerationPopup::giveMeData, this,
          [&]() {
            QJsonObject json;
            json[test::json::ID] = _client.generateRandomString();
            json[test::json::NAME] = _client.generateRandomString();
            json[test::json::NUMBER] = _client.generateRandomString();
            _dataGenerationPopup->setData(json);
          });
}

void MainWindow::connectNoPopButtons() {
  connect(ui->connectButton, &QPushButton::clicked, this, [&]() {
    _client.connectToServer(ui->linePort->text().toUShort(),
                            ui->lineHost->text());
  });
  connect(ui->getMessageCount, &QPushButton::clicked, this,
          [&]() { _client.getMessageCount(); });
  connect(&_client, &test::Client::messageCount, this,
          [this](QString count) { ui->responseLabel->setText(count); });
  connect(
      &_client, &test::Client::postedByClient, this,
      [this](QString postStatus) { ui->responseLabel->setText(postStatus); });

  connect(ui->getView, &QPushButton::clicked, this,
          [&]() { _client.getView(); });
}
