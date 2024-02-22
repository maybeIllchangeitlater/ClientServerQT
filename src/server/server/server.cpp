#include "server.h"

namespace test{

void Server::incomingConnection(qintptr socketDescriptor) {
  qDebug() << "new client connected " << socketDescriptor;
  QTcpSocket *socket = new QTcpSocket(this);
  socket->setSocketDescriptor(socketDescriptor);

  connect(socket, &QTcpSocket::readyRead, this, &Server::processRequest);

  connect(socket, &QTcpSocket::disconnected, socket,
          &QTcpSocket::deleteLater);
}

void Server::processRequest()  {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QByteArray requestData = socket->readAll();
    QString path = parseURI(requestData);
    QString connectionStatus = parseConnectionStatus(requestData);

    if (path == http::uri::STRING) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postString(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::JSON) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postJson(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::BINARY) {
      workRequest(
          [&](const QByteArray &data) { return _controller.postBinary(data); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::MESSAGE_COUNT) {
      workRequest(
          [&](const QByteArray &) { return _controller.getMessageCount(); },
          requestData, socket, connectionStatus);
    } else if (path == http::uri::VIEW) {
      workRequest([&](const QByteArray &) { return _controller.getView(); },
                  requestData, socket, connectionStatus);
    } else if (path == http::uri::CLOSE_CONNECTION) {
      socket->write(http::headers::HEADER_OK);
      writeResponse("", socket, http::headers::CONNECTION_STATUS_CLOSE);
    }
  }

template <typename Handler>
void Server::workRequest(const Handler &handler, const QByteArray &data,
                 QTcpSocket *socket, const QString &connectionStatus) {
  try {
    QByteArray response = handler(data);
    socket->write(http::headers::HEADER_OK);
    writeResponse(response, socket, connectionStatus);
  } catch (const std::exception &e) {
    socket->write(http::headers::HEADER_BAD_REQUEST);
    writeResponse(e.what(), socket, http::headers::CONNECTION_STATUS_CLOSE);
  }
}

void Server::writeResponse(const QString &data, QTcpSocket *socket,
                   const QString &connectionStatus) {
  if (!data.isEmpty()) {
    socket->write(http::headers::CONTENT_LENGTH_HEADER +
                  QByteArray::number(data.size()) +
                  http::headers::HEADER_DELIMITER);
    socket->write(http::headers::CONTENT_TYPE_HEADER);
    socket->write(http::headers::PLAIN_TEXT);
    socket->write(http::headers::HEADERS_END);
    socket->write(data.toUtf8());
  } else {
    socket->write(http::headers::CONTENT_LENGTH_HEADER +
                  QByteArray::number(0));
    socket->write(http::headers::HEADERS_END);
  }
  socket->flush();
  socket->waitForBytesWritten();
  if (connectionStatus == http::headers::CONNECTION_STATUS_CLOSE) {
    qDebug() << "ending session with " << socket->socketDescriptor();
    socket->disconnectFromHost();
  }
}

QString Server::parseURI(const QByteArray &requestData) const {
  qsizetype pathIndex = requestData.indexOf('/');
  qsizetype protocolIndex = requestData.indexOf("HTTP/1.1");
  if (pathIndex != -1 && protocolIndex != -1 && protocolIndex > pathIndex) {
    return requestData.mid(pathIndex,
                           requestData.indexOf("HTTP/1.1") - pathIndex - 1);
  } else {
    throw std::logic_error("invalid HTTP request");
  }
}

QString Server::parseConnectionStatus(const QByteArray &requestData) const {
  qsizetype connectionHeaderIndex =
      requestData.indexOf(http::headers::CONNECTION_HEADER);
  if (connectionHeaderIndex != -1) {
    qsizetype connectionHeaderEndIndex = requestData.indexOf(
        http::headers::HEADER_DELIMITER, connectionHeaderIndex);
    if (connectionHeaderEndIndex != -1) {
      QString connectionHeader =
          requestData.mid(connectionHeaderIndex,
                          connectionHeaderEndIndex - connectionHeaderIndex);
      QString status = connectionHeader.split(":").last().trimmed();
      return status;
    }
  }
  throw std::logic_error("invalid HTTP request");
}


}
