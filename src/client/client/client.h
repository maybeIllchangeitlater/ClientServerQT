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
     * @brief connectToServer подключение к серверу
     * @param port порт сервера
     */
    void connectToServer(unsigned short port, const QString &host = "localhost");

    /**
     * @brief post отправляет POST запрос на сервер
     * @param data дата для POST (QString, QJsonObject, binary file)
     * @param handler что случится после получения ответа
     * @param connectionStatus статус соединения
     */
    template<typename T, typename Handler>
    void post(T &&data, Handler &&handler,
              http::RequestGenerator::ConnectionStatus connectionStatus
              = http::RequestGenerator::ConnectionStatus::CLOSE);
    /**
     * @brief getMessageCount отправляет GET количества сообщений запрос на сервер
     */
    void getMessageCount();

    /**
     * @brief getView отправляет GET view запрос на сервер
     */
    void getView();
    /**
     * @brief generateRandomString производит случайную строку
     * @return случайно сгенерированную строку
     */
    QString generateRandomString();

 public slots:
    /**
     * @brief postString from view
     */
    void postString(QString string);
    /**
   * @brief handlePingReplyFinished обрабатывает ответ пингов к серверу
   */
  void handlePingReplyFinished();
  /**
   * @brief handlePostReplyFinished обрабатывает ответ пост запросов к серверу
   */
  void handlePostReplyFinished();
  /**
   * @brief handleGetMessageCountFinished обрабатывает ответ на получение количества сообщений от сервера
   */
  void handleGetMessageCountFinished();
  /**
   * @brief handleGetViewFinished обрабатывает ответ на получений view из сервера
   */
  void handleGetViewFinished();

signals:
    void messageCount(QString);
    void viewRecieved(QByteArray);
    void postedByClient(QString);

 private:
  /**
   * @brief closeSession отправить запрос на закрытие сессии
   */
  void closeSession();
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
  QTimer _pingTimer;
  std::unique_ptr<RandomStringGenerator> _randomStringGenerator;
  http::RequestGenerator _requestGenerator;
  std::atomic<unsigned short> _pingCounter;
  unsigned short _hostPort;
};

}  // namespace test

#endif //CLIENTSERVERQT_CLIENT_CLIENT_CLIENT_H_
