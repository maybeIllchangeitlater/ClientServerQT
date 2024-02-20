#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(test::Server &server, QWidget *parent)
    : QMainWindow(parent),
      _server(server),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server.listen(QHostAddress::LocalHost, 8888);
}

MainWindow::~MainWindow()
{
    delete ui;
}

