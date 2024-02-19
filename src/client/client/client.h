#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

#include <QTcpSocket>

namespace test{

class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(unsigned short port = 8888);

    void connectToServer(unsigned short port);
    void disconnectFromServer();
    void sendRequest(const QByteArray &requestData);

signals:
    void responseReceived(const QByteArray &responseData);

private slots:
    void onConnected() {
        qDebug() << "Connected to server.";
    }

    void onDisconnected() {
        qDebug() << "Disconnected from server.";
    }

    void onReadyRead() {
        qDebug() << "Response received.";
        QByteArray responseData = _socket.readAll();
        qDebug() << responseData;
        emit responseReceived(responseData);
    }

private:
    QTcpSocket _socket;
    unsigned short _hostPort;


};
} //test

#endif //CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
