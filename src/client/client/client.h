#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <thread>

#include "../common/data.h"
#include "../common/utility/requestGenerator.h"

namespace test {

class Client : public QObject {
  Q_OBJECT
 public:
    /**
   * @brief Client создает объект клиента, который пытается подключится к сереверу на localhost:port
   * @param port сервера
   */
  explicit Client(unsigned short port = 8888);

 signals:
    /**
   * @brief responseReceived пришел ответ от сервера
   * @param responseData ответ
   */
  void responseReceived(const QByteArray &responseData);

 private slots:
  /**
   * @brief onRequestFinished запрос обработан
   * @param reply ответ
   */
  void onRequestFinished(QNetworkReply *reply);

 private:
  /**
   * @brief connectToServer подключение к серверу
   * @param port порт сервера
   */
  void connectToServer(unsigned short port);
  /**
   * @brief disconnectFromServer отключиться от сервера
   */
  void disconnectFromServer();
  /**
   * @brief startPingingServer начать посылать запросы серверу с переодичностью 1 секунда
   */
  void startPingingServer();
  /**
   * @brief pingServer отправить серверу пост запросы
   */
  void pingServer();
  http::RequestGenerator _requestGenerator;
  QTcpSocket _socket;
  QNetworkAccessManager _manager;
  QTimer _pingTimer;
  unsigned short _hostPort;
};

}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
