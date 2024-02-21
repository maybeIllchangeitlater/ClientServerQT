#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>
#include <memory>

#include "../common/data.h"
#include "../common/randomStringGenerator.h"
#include "../common/dateTime.h"
#include "utility/requestGenerator.h"

namespace test {
/**
 * @brief The Client class предоставляющий функциональность клиента для передачи
 * и получения данных от сервера
 */
class Client : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Client создает объект клиента, который пытается подключится к
   * сереверу на localhost:port
   * @param port сервера
   */
  explicit Client(unsigned short port = 8888);

    template<typename T>
    void send(T &&data);
    /**
     * @brief sendString отправляет случайно сгенерированную строку на сервер
     */
//    void sendString();
//    /**
//     * @brief sendString отправляет строку на сервер
//     * @param stringToSend строка для отправки
//     */
//    void sendString(const QString &stringToSend);
//    /**
//     * @brief sendData отправляет случайно сгенерированную data на сервер
//     */
//    void sendData();
//    /**
//     * @brief sendData отправляет data на сервер
//     * @param data для отправки
//     */
//    void sendData(const Data &data);

 signals:
  /**
   * @brief responseReceived пришел ответ от сервера
   * @param responseData ответ
   */
  void responseReceived(const QByteArray &responseData);

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
   * @brief startPingingServer начать посылать запросы серверу с переодичностью
   * 1 секунда
   */
  void startPingingServer();
  /**
   * @brief pingServer отправить серверу пост запросы
   */
  void pingServer();
private:
  QNetworkAccessManager _manager;
  QTcpSocket _socket;
  QTimer _pingTimer;
  std::unique_ptr<RandomStringGenerator> _randomStringGenerator;
  http::RequestGenerator _requestGenerator;
  unsigned short _hostPort;
  DateTime _dateTimeStamper;
};

}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

//#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
//#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H

//#include <QDebug>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QNetworkRequest>
//#include <QObject>
//#include <QTcpSocket>
//#include <QTimer>
//#include <thread>

//#include "../common/data.h"
//#include "utility/requestGenerator.h"

//namespace test {
///**
// * @brief The Client class предоставляющий функциональность клиента для передачи
// * и получения данных от сервера
// */
//class Client : public QObject {
//  Q_OBJECT
// public:
//  /**
//   * @brief Client создает объект клиента, который пытается подключится к
//   * сереверу на localhost:port
//   * @param port сервера
//   */
//  explicit Client(unsigned short port = 8888);

//        template<typename T>
//        void send(T &&data);

// signals:
//  /**
//   * @brief responseReceived пришел ответ от сервера
//   * @param responseData ответ
//   */
//  void responseReceived(const QByteArray &responseData);

// private slots:
//  /**
//   * @brief onRequestFinished запрос обработан
//   * @param reply ответ
//   */
//  void onRequestFinished(QNetworkReply *reply);

// private:
//  /**
//   * @brief connectToServer подключение к серверу
//   * @param port порт сервера
//   */
//  void connectToServer(unsigned short port);
//  /**
//   * @brief disconnectFromServer отключиться от сервера
//   */
//  void disconnectFromServer();
//  /**
//   * @brief startPingingServer начать посылать запросы серверу с переодичностью
//   * 1 секунда
//   */
//  void startPingingServer();
//  /**
//   * @brief pingServer отправить серверу пост запросы
//   */
//  void pingServer();
//  http::RequestGenerator _requestGenerator;
//  QTcpSocket _socket;
//  QNetworkAccessManager _manager;
//  QTimer _pingTimer;
//  unsigned short _hostPort;
//};

//}  // namespace test

//#endif  // CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H
