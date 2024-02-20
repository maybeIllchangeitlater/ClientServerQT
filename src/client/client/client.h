#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <thread>
#include <QDebug>
#include "../utility/requestGenerator.h"
#include "../common/data.h"

namespace test {

class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(unsigned short port = 8888);

    void connectToServer(unsigned short port);
    void disconnectFromServer();
//    void sendRequest(const QByteArray &requestData);
    void startPingingServer();

signals:
    void responseReceived(const QByteArray &responseData);

private slots:
    void onRequestFinished(QNetworkReply *reply);

private:
    http::RequestGenerator _requestGenerator;
    QTcpSocket _socket;
    QNetworkAccessManager _manager;
    std::thread _pingThread;
    unsigned short _hostPort;
};

} // namespace test

#endif // CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
