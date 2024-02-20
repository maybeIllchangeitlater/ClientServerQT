#ifndef CLIENTSERVERQT_COMMON_DATA_H
#define CLIENTSERVERQT_COMMON_DATA_H

#include <QFile>
#include <QJsonObject>
#include <QString>

#include "../client/utility/randomStringGenerator.h"
#include "utility/dateTime.h"

namespace test {
class Data {
 public:
  /**
   * @brief Data конструктор генерирующий случайно заполненную дату
   * @param randStringGen генератор случайных строк
   * @param dateTimeStamper для получения текущей даты и времен
   */
  Data(RandomStringGenerator &randStringGen, DateTime &dateTimeStamper)
      : _name(randStringGen.generateNumCharString()),
        _id(randStringGen.generateNumCharString()),
        _number(randStringGen.generateNumOnlyString()) {
    auto [date, time] = dateTimeStamper.GetDateTime();
    _date = std::move(date);
    _time = std::move(time);
  }

  /**
   * @brief Data конструктор на основе json объекта
   * @param json на котором будет основан обект
   */
  Data(const QJsonObject &json)
      : _name(json["name"].toString()),
        _id(json["id"].toString()),
        _number(json["number"].toString()),
        _date(json["date"].toString()),
        _time(json["time"].toString()) {}
  /**
   * @brief Data конструктор на основе бинарного файла
   * @param filePath путь до бинарного файла
   */
  Data(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
      throw std::runtime_error("Cannot open " + filePath.toStdString() +
                               " file for reading");
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_5);

    in >> _name >> _id >> _number >> _date >> _time;

    file.close();
  }

  /**
   * @brief toJson создает json на основе даты
   * @return json представление даты
   */
  QJsonObject toJson() const {
    QJsonObject json;
    json["name"] = _name;
    json["id"] = _id;
    json["number"] = _number;
    json["date"] = _date;
    json["time"] = &time;
    return json;
  }
  /**
   * @brief writeToBinaryFile создает бинарный файл на основе даты
   * @param filePath путь к бинарному файлу
   */
  void writeToBinaryFile(const QString &filePath) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
      throw std::runtime_error("Cannot open " + filePath.toStdString() +
                               " file for writing");
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_5);

    out << _name << _id << _number << _date << _time;

    file.close();
  }

 private:
  QString _name;    // json: "name"
  QString _id;      // json: "id"
  QString _number;  // json: "number"
  QString _date;    // json: "date"
  QString _time;    // json: "time"
};
}  // namespace test

#endif  // CLIENTSERVERQT_COMMON_DATA_H
