#ifndef CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
#define CLIENTSERVERQT_SERVER_SERVER_SERVER_H_


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QUrl>
#include <QMap>
#include "../controller/controller.h"


namespace test {


class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(Controller& controller, QObject *parent = nullptr)
        : _controller(controller), QTcpServer(parent) {}

protected:
    /**
     * @brief incomingConnection принимает входящие соединение
     * @param socketDescriptor описание сокета клиента
     */
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);

        connect(socket, &QTcpSocket::readyRead, this, [=]() {
            processRequest(socket);
        });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }

private:
    /**
     * @brief processRequest обрабатывает запрос посланный клиентом (POST 1 из 3 типов даты или GET количества сообщений в бд)
     * @param socket сокет клиента
     */
    void processRequest(QTcpSocket *socket) {
        QByteArray requestData = socket->readAll();
        if(!requestData.contains("POST")){
            qDebug() << requestData;
        }
        if (requestData.contains("/text-data")) {
            _controller.postString(requestData);
        } else if (requestData.contains("/structured-data")) {
            _controller.postJson(requestData);
        } else if (requestData.contains("/message-count")){
            QString msgCount = _controller.getMessageCount();
            QByteArray data = msgCount.toUtf8();
            socket->write("HTTP/1.1 200 OK\r\n");
                socket->write("Content-Length: " + QByteArray::number(data.size()) + "\r\n");
                socket->write("Content-Type: text/plain\r\n");
                socket->write("\r\n"); // End of headers
                socket->write(data);
                socket->flush(); // Ensure that the data is sent immediately
                socket->waitForBytesWritten(); // Wait for bytes to be written
                socket->disconnectFromHost();
                return;

        }

        QByteArray data = "Hello from server!";
        socket->write("HTTP/1.1 200 OK\r\n");
            socket->write("Content-Length: " + QByteArray::number(data.size()) + "\r\n");
            socket->write("Content-Type: text/plain\r\n");
            socket->write("\r\n"); // End of headers
            socket->write(data);
            socket->flush(); // Ensure that the data is sent immediately
            socket->waitForBytesWritten(); // Wait for bytes to be written
            socket->disconnectFromHost();
    }

    Controller& _controller;
};
} //test
#endif //CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
