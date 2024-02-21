#include "client.h"

namespace test {

Client::Client(unsigned short port) : _hostPort(port), _manager(this) {
  connectToServer(_hostPort);
}

void Client::connectToServer(unsigned short port) {
  if (_socket.isOpen()) {
    disconnectFromServer();
  }
  _hostPort = port;
  _requestGenerator.setHostPort(port);
  _socket.connectToHost("127.0.0.1", _hostPort);
  if (!_socket.waitForConnected()) {
    throw std::runtime_error(
        "failed to connect to server on port: " + std::to_string(_hostPort) +
        " " + _socket.errorString().toStdString());
  }
  startPingingServer();
}

void Client::disconnectFromServer() {
  if (_socket.isOpen()) {
    _socket.disconnectFromHost();
  }
}

void Client::startPingingServer() {
  connect(&_pingTimer, &QTimer::timeout, this, &Client::pingServer);
  _pingTimer.start(20000);
}

void Client::pingServer() {
  auto [requestString, bodyString] =
      _requestGenerator.generatePostRandomStringRequest();
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

  auto [requestJson, bodyJson] =
      _requestGenerator.generatePostRandomJsonRequest();

  QNetworkReply *replyJson = _manager.post(requestJson, bodyJson);
  connect(replyJson, &QNetworkReply::finished, [=]() {
    if (replyJson->error() == QNetworkReply::NoError) {
      QByteArray response = replyJson->readAll();
      qDebug() << response;
      // do something with the data...
    } else  // handle error
    {
      qDebug() << replyJson->errorString();
    }
  });

  auto requestCount = _requestGenerator.getMessageCount();
  QNetworkReply *replyCount = _manager.get(requestCount);
  connect(replyCount, &QNetworkReply::finished, [=]() {
    if (replyCount->error() == QNetworkReply::NoError) {
      QByteArray response = replyCount->readAll();
      qDebug() << response;
      // do something with the data...
    } else  // handle error
    {
      qDebug() << replyCount->errorString();
    }
  });

  auto requestView = _requestGenerator.getView();
  QNetworkReply *replyView = _manager.get(requestView);
  connect(replyView, &QNetworkReply::finished, [=]() {
    if (replyView->error() == QNetworkReply::NoError) {
      QByteArray response = replyView->readAll();
      qDebug() << response;
      // do something with the data...
    } else  // handle error
    {
      qDebug() << replyView->errorString();
    }
  });
}

void Client::onRequestFinished(QNetworkReply *reply) {
  if (reply) {
    if (reply->error() == QNetworkReply::NoError) {
      QByteArray responseData = reply->readAll();
      qDebug() << responseData;
      // Process the response data here
      emit responseReceived(responseData);
    } else {
      qDebug() << "Error occurred:" << reply->errorString();
    }
    reply->deleteLater();
  }
}

}  // namespace test
