#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _client()
{
    ui->setupUi(this);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectToServer);
    connect(ui->getMessageCount, &QPushButton::clicked, this, &MainWindow::getMessageCount);
    connect(&_client, &test::Client::messageCount, this, [this](QString count){
           ui->responseLabel->setText(count);
     });
}

void MainWindow::connectToServer() {
    _client.connectToServer(ui->linePort->text().toUShort(), ui->lineHost->text());
}

void MainWindow::getMessageCount(){
    _client.getMessageCount();
}

MainWindow::~MainWindow()
{
    delete ui;
}

