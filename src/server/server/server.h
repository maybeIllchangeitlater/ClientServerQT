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

        connect(socket, &QTcpSocket::readyRead, this, &Server::processRequest);

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }

private slots:
    /**
     * @brief processRequest обрабатывает запрос посланный клиентом (POST 1 из 3 типов даты или GET количества сообщений принятых сервером/view из бд)
     */
    void processRequest() {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        QByteArray requestData = socket->readAll();
        QString path = parseURI(requestData);
        QString connectionStatus = parseConnectionStatus(requestData);
        qDebug() << path;
        qDebug() << requestData;
        if (path == "/text-data") {
            _controller.postString(requestData);
        } else if (path == "/structured-data") {
            _controller.postJson(requestData);
        } else if (path == "/message-count"){
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
        } else if(path == "/view"){
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
        } else if(path == "/file-upload"){
            _controller.postBinary(requestData);
        } else if(path == "/close"){
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
private:
    /**
     * @brief parseURI извлекает идентефикатор ресурсов из пришедшего реквеста
     * @param requestData реквест
     * @return путь
     */
    QString parseURI(const QByteArray &requestData) const {
        qsizetype pathIndex = requestData.indexOf('/');
        qsizetype protocolIndex = requestData.indexOf("HTTP/1.1");
        if (pathIndex != -1 && protocolIndex != -1 && protocolIndex > pathIndex){
            return requestData.mid(pathIndex, requestData.indexOf("HTTP/1.1") - pathIndex - 1);
        }else {
            throw std::logic_error("invalid HTTP request");
        }
    }
    /**
     * @brief getConnectionStatus извлекает статус подключения из пришедшего реквеста
     * @param requestData реквест
     * @return статус подключения
     */
    QString parseConnectionStatus(const QByteArray &requestData) const {
        qsizetype connectionHeaderIndex = requestData.indexOf("Connection:");
        if (connectionHeaderIndex != -1){
            qsizetype connectionHeaderEndIndex = requestData.indexOf("\r\n", connectionHeaderIndex);
            if(connectionHeaderEndIndex != -1) {
                QString connectionHeader = requestData.mid(connectionHeaderIndex, connectionHeaderEndIndex - connectionHeaderIndex);
                QString status = connectionHeader.split(":").last().trimmed();
                return status;
            }
        }
        throw std::logic_error("invalid HTTP request");
    }
    Controller& _controller;
};
} //test
#endif //CLIENTSERVERQT_SERVER_SERVER_SERVER_H_
