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
  startPingingServer();
}

template<typename T>
void Client::send(T &&data){

      auto [requestString, bodyString] =
          _requestGenerator.generatePostRequest(std::move(data));
      QNetworkReply *replyString = _manager.post(requestString, bodyString);
      connect(replyString, &QNetworkReply::finished, [=]() {
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
//    QString vrot("v rot ebla");
//    send(QString(vrot));
    send(_randomStringGenerator->generateNumCharString());
//    QString govno = _requestGenerator.generatePostRandomStringRequest();
//    QString govno("govno");
//    send(govno);
//  auto [requestString, bodyString] =
//      _requestGenerator.generatePostRandomStringRequest();
//  QNetworkReply *replyString = _manager.post(requestString, bodyString);
//  connect(replyString, &QNetworkReply::finished, [=]() {
//    if (replyString->error() == QNetworkReply::NoError) {
//      QByteArray response = replyString->readAll();
//      qDebug() << response;
//      // do something with the data...
//    } else  // handle error
//    {
//      qDebug() << replyString->errorString();
//    }
//  });

//  auto [requestJson, bodyJson, data] =
//      _requestGenerator.generatePostRandomJsonRequest();

//  QNetworkReply *replyJson = _manager.post(requestJson, bodyJson);
//  connect(replyJson, &QNetworkReply::finished, [=]() {
//    if (replyJson->error() == QNetworkReply::NoError) {
//      QByteArray response = replyJson->readAll();
//      qDebug() << response;
//      // do something with the data...
//    } else  // handle error
//    {
//      qDebug() << replyJson->errorString();
//    }
//  });

//  auto binaryFile = "/Users/monke/Desktop/" + data.GetTime() + ".bin";
//  data.writeToBinaryFile(binaryFile);

//  auto [requestBinary, bodyBinary] =
//      _requestGenerator.generatePostBinaryRequest(binaryFile);

//          Data test(binaryFile);
//          qDebug() << test.GetName() << test.GetId() << test.GetNumber() << test.GetDate() << test.GetTime();

//  QNetworkReply *replyBinary = _manager.post(requestBinary, bodyBinary);
//  connect(replyBinary, &QNetworkReply::finished, [=]() {
//    if (replyBinary->error() == QNetworkReply::NoError) {
//      QByteArray response = replyBinary->readAll();
//      qDebug() << response;
//      // do something with the data...
//    } else  // handle error
//    {
//      qDebug() << replyBinary->errorString();
//    }
//  });

//  auto requestCount = _requestGenerator.getMessageCount();
//  QNetworkReply *replyCount = _manager.get(requestCount);
//  connect(replyCount, &QNetworkReply::finished, [=]() {
//    if (replyCount->error() == QNetworkReply::NoError) {
//      QByteArray response = replyCount->readAll();
//      qDebug() << response;
//      // do something with the data...
//    } else  // handle error
//    {
//      qDebug() << replyCount->errorString();
//    }
//  });

//  auto requestView = _requestGenerator.getView();
//  QNetworkReply *replyView = _manager.get(requestView);
//  connect(replyView, &QNetworkReply::finished, [=]() {
//    if (replyView->error() == QNetworkReply::NoError) {
//      QByteArray response = replyView->readAll();
//      qDebug() << response;
//      // do something with the data...
//    } else  // handle error
//    {
//      qDebug() << replyView->errorString();
//    }
//  });
}

}  // namespace test
