#ifndef CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
#define CLIENTSERVERQT_SERVER_SERVER_SERVER_H_


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QUrl>
#include <QMap>
#include "../controller/stringController.h"
#include "../controller/jsonController.h"


namespace test {


class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(StringController& stringController, JsonController& jsonController, QObject *parent = nullptr)
        : _stringController(stringController), _jsonController(jsonController), QTcpServer(parent) {}

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

        if (requestData.contains("/text-data")) {
            _stringController.postString(requestData);
        } else if (requestData.contains("structured-data")) {
            _jsonController.postJson(requestData);
        } else if (requestData.contains("GET")){
            qDebug() << "string count: " << _stringController.getStringCount();
            qDebug() << "json count: " << _jsonController.getJsonCount();

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

    StringController &_stringController;
    JsonController &_jsonController;
};
} //test
#endif //CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
