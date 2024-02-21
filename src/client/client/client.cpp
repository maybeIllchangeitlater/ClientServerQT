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

template<typename T>
void Client::post(T &&data){

      auto [requestString, bodyString] =
          _requestGenerator.generatePostRequest(std::move(data));
      QNetworkReply *replyString = _manager.post(requestString, bodyString);
      connect(replyString, &QNetworkReply::finished, [=]() {
         _pingCounter.fetch_add(1);
        if (replyString->error() == QNetworkReply::NoError) {
          QByteArray response = replyString->readAll();
          qDebug() << response;
          // do something with the data...
        } else  // handle error
        {
          qDebug() << replyString->errorString();
        }
        if (_pingCounter.load() == 3) {
                closeSession();
            }

      });
}

void Client::closeSession() {
    auto request = _requestGenerator.closeSessionRequest();
    QNetworkReply *replyString = _manager.deleteResource(request);
    connect(replyString, &QNetworkReply::finished, [=]() {
       _pingCounter.fetch_add(1);
      if (replyString->error() == QNetworkReply::NoError) {
        QByteArray response = replyString->readAll();
        qDebug() << response;
        // do something with the data...
      } else  // handle error
      {
        qDebug() << replyString->errorString();
      }

    });
}

void Client::startPingingServer() {
  connect(&_pingTimer, &QTimer::timeout, this, &Client::pingServer);
  _pingTimer.start(5000);
}

void Client::pingServer() {
    _pingCounter.store(0);
    post(_randomStringGenerator->generateNumCharString());
    Data data(_randomStringGenerator, _dateTimeStamper);
    post(data.toJson());
    QString binaryFilepath = data.GetName() + ".bin";
    data.writeToBinaryFile(binaryFilepath);
    QFile binaryFile(binaryFilepath);
    if (!binaryFile.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("failure opening binary file");
    }
    post(std::move(binaryFile));
}

}  // namespace test



///keep connection alive header (false after all sent)
