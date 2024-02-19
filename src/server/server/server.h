#ifndef CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
#define CLIENTSERVERQT_SERVER_SERVER_SERVER_H_


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QUrl>
#include <QMap>
#include "../../common/http/response.h"
#include "../../common/http/statusMessage.h"
#include "../../common/http/header.h"
#include "../../common/enums/contentType.h"


namespace test {


class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    /**
     * @brief incomingConnection accepts incoming connections
     * @param socketDescriptor client's socket descriptor
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
     * @brief processRequest sent by client (Either POST 1 of 3 data types or GET amount of already stored messages)
     * @param socket clients socket
     */
    void processRequest(QTcpSocket *socket) {

        QByteArray requestData = socket->readAll();
        if (requestData.startsWith("POST")) {

            QString content = QString(requestData);
            qDebug() << "Received POST request:" << content;
            // Save data to the database//
            auto response = http::Response(http::OK, http::Header());
            socket->write(response.toByteArray());

        } else if (requestData.startsWith("GET")) {
            // Retrieve count of messages saved in the database
            // Respond with HTTP 200 OK containing the count
            qDebug() << "Received GET request";
            // Retrieve count of messages from the database
            int messageCount = getMessageCount(); // Dummy function, you should implement this
            QByteArray body(std::to_string(messageCount).data());
            auto header = http::Header(http::PLAIN_TEXT, body.length());
            auto response = http::Response(http::OK, header, body.data());
            socket->write(response.toByteArray());;
        } else {
            auto response = http::Response(http::BAD_REQUEST, http::Header());
            socket->write(response.toByteArray());
        }

        socket->waitForBytesWritten();
        socket->disconnectFromHost();
    }

    int getMessageCount() {
        // Retrieve the count of messages saved in the database
        // Dummy function, you should implement this
        return 0;
    }
};
} //test
#endif //CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
