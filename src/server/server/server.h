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

/**
 * @brief The Server class предоставляющий функционал сервера для передачи и получения данных от клиента
 */
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
        qDebug() << "new client connected " << socketDescriptor;
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
        qDebug() << "got new request";
        QByteArray requestData = socket->readAll();
//        if(!requestData.contains("POST")){
//            qDebug() << requestData;
//        }
        if (requestData.contains("/text-data")) {
            _controller.postString(requestData);
        } else if (requestData.contains("/structured-data")) {
            _controller.postJson(requestData);
        } else if (requestData.contains("/message-count")){
            QByteArray data = _controller.getMessageCount();
            socket->write("HTTP/1.1 200 OK\r\n");
                socket->write("Content-Length: " + QByteArray::number(data.size()) + "\r\n");
                socket->write("Content-Type: text/plain\r\n");
                socket->write("\r\n"); // End of headers
                socket->write(data);
                socket->flush(); // Ensure that the data is sent immediately
                socket->waitForBytesWritten(); // Wait for bytes to be written
                socket->disconnectFromHost();
                return;
        } else if(requestData.contains("/view")){
            QByteArray data = _controller.getView();
            socket->write("HTTP/1.1 200 OK\r\n");
            socket->write("Content-Length: " + QByteArray::number(data.size()) + "\r\n");
            socket->write("Content-Type: text/plain\r\n");
            socket->write("\r\n"); // End of headers
            socket->write(data);
            socket->flush(); // Ensure that the data is sent immediately
            socket->waitForBytesWritten(); // Wait for bytes to be written
            socket->disconnectFromHost();
            return;
        } else if(requestData.contains("/file-upload")){
            _controller.postBinary(requestData);
        } else if(requestData.contains("/close")){
            QByteArray data = "Killed";
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
    }

    Controller& _controller;
};
} //test
#endif //CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
