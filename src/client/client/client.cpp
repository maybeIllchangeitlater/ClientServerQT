#include "client.h"
#include <QDebug>

namespace test {

Client::Client(unsigned short port)
    : _hostPort(port), _manager(this),
    _randomStringGenerator(std::make_unique<RandomStringGenerator>()) {
  connectToServer(_hostPort);
}

void Client::connectToServer(unsigned short port) {
    _hostPort = port;
    _requestGenerator.setHostPort(port);
    _manager.connectToHost("loaclhost", 8888);
    startPingingServer();
}

void Client::closeSession() {
    auto request = _requestGenerator.closeSessionRequest();
    QNetworkReply *reply = _manager.deleteResource(request);
    reply->deleteLater(); //reply not important here
}

template<typename T, typename Handler>
void Client::post(T &&data, Handler &&handler){
      auto [request, body] =
          _requestGenerator.generatePostRequest(std::move(data));
      QNetworkReply *reply = _manager.post(request, body);
      connect(reply, &QNetworkReply::finished, this, handler);
}

void Client::getMessageCount(){
    auto request = _requestGenerator.getMessageCountRequest();
    QNetworkReply *reply = _manager.get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
          QByteArray response = reply->readAll();
          qDebug() << response;
          // do something with the data...
        } else  // handle error
        {
          qDebug() << reply->errorString();
        }
    });

    reply->deleteLater();
}

void Client::getView() {
    auto request = _requestGenerator.getViewRequest();
    QNetworkReply *reply = _manager.get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
          QByteArray response = reply->readAll();
          qDebug() << response;
          // do something with the data...
        } else  // handle error
        {
          qDebug() << reply->errorString();
        }
    });

    reply->deleteLater();
}

void Client::startPingingServer() {
  connect(&_pingTimer, &QTimer::timeout, this, &Client::pingServer);
  _pingTimer.start(5000);
}

void Client::pingServer() {
    _pingCounter.store(0);
    post(_randomStringGenerator->generateNumCharString(), &Client::handlePingReplyFinished);
    Data data(_randomStringGenerator, _dateTimeStamper);
    post(data.toJson(), &Client::handlePingReplyFinished);
    QString binaryFilepath = data.GetName() + ".bin";
    data.writeToBinaryFile(binaryFilepath);
    QFile binaryFile(binaryFilepath);
    if (!binaryFile.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("failure opening binary file");
    }
    post(std::move(binaryFile), &Client::handlePingReplyFinished);
}

void Client::handlePingReplyFinished() {
    _pingCounter.fetch_add(1);
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << response;
        // Process the response data...
    } else {
        qDebug() << reply->errorString();
    }

    if (_pingCounter.load() == 3) {
        closeSession();
    }
    reply->deleteLater();
}

void Client::handlePostReplyFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << response;
        // Process the response data...
    } else {
        qDebug() << reply->errorString();
    }
    reply->deleteLater();
}

}  // namespace test
