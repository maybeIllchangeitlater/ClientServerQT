#include "client.h"

namespace test{
Client::Client(unsigned short port) : _hostPort(port){
    connect(&_socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(&_socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(&_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(unsigned short port) {
    if(_socket.isOpen()){
        disconnectFromServer();
    }
    _hostPort = port;
    _socket.connectToHost("127.0.0.1", _hostPort);
    if (!_socket.waitForConnected()) {
            throw std::runtime_error("failed to connect to server on port: " + std::to_string(_hostPort) + " " +
                                     _socket.errorString().toStdString());
    }
}

void Client::disconnectFromServer(){
    if(_socket.isOpen()){
        _socket.disconnectFromHost();
    }
}

void Client::sendRequest(const QByteArray &requestData){
    if(_socket.isOpen()){
        _socket.write(requestData);
        _socket.waitForBytesWritten();
    }else {
        throw std::logic_error("not connected to server");
    }
}

}
