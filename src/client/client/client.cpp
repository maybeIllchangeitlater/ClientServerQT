#include "client.h"

namespace test {

Client::Client(unsigned short port) : _hostPort(port) {
    connect(&_manager, &QNetworkAccessManager::finished, this, &Client::onRequestFinished);
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
        throw std::runtime_error("failed to connect to server on port: " + std::to_string(_hostPort) + " " +
                                 _socket.errorString().toStdString());
    }
}

void Client::disconnectFromServer() {
    if (_socket.isOpen()) {
        _socket.disconnectFromHost();
    }
}


void Client::startPingingServer() {
    _pingThread = std::thread([=](){
        auto[requestString, bodyString] = _requestGenerator.GeneratePostRandomStringRequest();
        QNetworkReply *replyString = _manager.post(requestString, bodyString);
        connect(replyString, &QNetworkReply::finished, this, &Client::onRequestFinished);

        auto[requestJson, bodyJson] = _requestGenerator.GeneratePostRandomJsonRequest();
        QNetworkReply *replyJson = _manager.post(requestJson, bodyJson);
        connect(replyJson, &QNetworkReply::finished, this, &Client::onRequestFinished);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

}

void Client::onRequestFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        // Process the response data here
        emit responseReceived(responseData);
    } else {
        qDebug() << "Error occurred:" << reply->errorString();
    }
    reply->deleteLater();
}

} // namespace test
