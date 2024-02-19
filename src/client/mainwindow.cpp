#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client.connectToServer(8888);
    client.sendRequest("GET Aboba");
}

MainWindow::~MainWindow()
{
    delete ui;
}

