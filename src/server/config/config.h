#ifndef CLIENTSERVERQT_SERVER_CONFIG_CONFIG_H_
#define CLIENTSERVERQT_SERVER_CONFIG_CONFIG_H_

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>

#include "../common/constants/configJsonNames.h"

namespace test {
/**
 * @brief The Config struct предоставляющая функционал настроек сервера
 */
struct Config {
  /**
   * @brief Config конструктор по умолчаную с параметрами по умолчанию для всех
   * настроек
   */
  Config()
      : databaseHost("localhost"),
        databaseName("test"),
        databaseUser("test"),
        databasePassword("test"),
        serverHost("127.0.0.1"),
        serverPort(8888),
        databasePort(5432) {}
  /**
   * @brief fromJsonFile фабричная функция для сборки config из json
   * @param jsonFilepath путь к json
   * @return Config на основе json или конфиг по умолчанию если файл отсутствует
   */
  static Config fromJsonFile(const QString &jsonFilepath) {
    QFile configFile(jsonFilepath);
    Config config;
    if (!configFile.open(QIODevice::ReadOnly)) {
      qDebug() << "failed to open config file, proceeding with default "
                  "configurations";
      config.Print();
      return config;
    }
    QByteArray jsonData = configFile.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
      qDebug() << "Failed to parse JSON:" << jsonError.errorString()
               << " proceeding with default configurations";
      config.Print();
      return config;
    }
    QJsonObject jsonObject = jsonDoc.object();

    if (jsonObject.contains(json::SERVER) &&
        jsonObject[json::SERVER].isObject()) {
      QJsonObject serverObject = jsonObject[json::SERVER].toObject();
      config.serverHost = serverObject[json::HOST].toString();
      config.serverPort = serverObject[json::PORT].toInt();
    } else {
      qDebug() << "No valid server configuration found"
               << " proceeding with default configurations";
      ;
      config.Print();
      return config;
    }
    if (jsonObject.contains(json::DATABASE) &&
        jsonObject[json::DATABASE].isObject()) {
      QJsonObject dbObject = jsonObject[json::DATABASE].toObject();
      config.databaseName = dbObject[json::DATABASE_NAME].toString();
      config.databaseUser = dbObject[json::USER].toString();
      config.databasePassword = dbObject[json::PASSWORD].toString();
      config.databaseHost = dbObject[json::HOST].toString();
      config.databasePort = dbObject[json::PORT].toInt();
    } else {
      qDebug() << "No valid database configuration found proceeding with "
                  "default settings for database";
      config.Print();
      return config;
    }
    qDebug() << "Loaded configuration from json";
    config.Print();
    return config;
  }
  /**
   * @brief DBSettingsString настройки базы данных в формате для
   * pqxx::connection
   * @return настройки базы данных
   */
  QString DBSettingsString() const {
    return "dbname=" + databaseName + " user=" + databaseUser +
           " password=" + databasePassword + " host=" + databaseHost +
           " port=" + QString::number(databasePort);
  }
  /**
   * @brief Print распечатывает конфиг
   */
  void Print() const {
    qDebug() << "Database: \n" << DBSettingsString();
    qDebug() << "server host: " << serverHost
             << "\tserver port: " << serverPort;
  }
  QString databaseHost;
  QString databaseName;
  QString databaseUser;
  QString databasePassword;
  QString serverHost;
  unsigned short serverPort;
  unsigned short databasePort;
};
}  // namespace test
#endif  // CLIENTSERVERQT_SERVER_CONFIG_CONFIG_H_
