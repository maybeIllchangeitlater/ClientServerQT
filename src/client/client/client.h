#ifndef CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H_
#define CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H_

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkInformation>

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

    /**
     * @brief post отправляет POST запрос на сервер
     * @param data дата для POST (QString, QJsonObject, binary file)
     */
    template<typename T>
    void post(T &&data);

 signals:
  /**
   * @brief responseReceived пришел ответ от сервера
   * @param responseData ответ
   */
  void responseReceived(const QByteArray &responseData);

 private:
  void closeSession();
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
  std::atomic<unsigned short> _pingCounter;
  unsigned short _hostPort;
  DateTime _dateTimeStamper;
};

}  // namespace test

#endif //CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H_
