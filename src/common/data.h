#ifndef CLIENTSERVERQT_COMMON_DATA_H_
#define CLIENTSERVERQT_COMMON_DATA_H_

#include <memory>
#include <QFile>
#include <QJsonObject>
#include <QString>

#include "../common/randomStringGenerator.h"
#include "../common/dateTime.h"
#include "../common/constants/jsonNames.h"

namespace test {
/**
 * @brief The Data class предоставляющий функционал создания случайного набора данных и сереализации/десериализации в json и бинарный файл
 */
class Data {
 public:
  /**
   * @brief Data конструктор генерирующий случайно заполненную дату
   * @param randStringGen генератор случайных строк
   * @param dateTimeStamper для получения текущей даты и времен
   */
  Data(std::unique_ptr<RandomStringGenerator> &randStringGen, DateTime &dateTimeStamper)
      : _name(randStringGen->generateNumCharString()),
        _id(randStringGen->generateNumCharString()),
        _number(randStringGen->generateNumOnlyString()) {
    auto [date, time] = dateTimeStamper.getDateTime();
    _date = std::move(date);
    _time = std::move(time);
  }

  /**
   * @brief Data конструктор на основе json объекта
   * @param json на котором будет основан обект
   */
  Data(const QJsonObject &json)
      : _name(json[json::NAME].toString()),
        _id(json[json::ID].toString()),
        _number(json[json::NUMBER].toString()),
        _date(json[json::DATE].toString()),
        _time(json[json::TIME].toString()) {}
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
    json[json::NAME] = _name;
    json[json::ID] = _id;
    json[json::NUMBER] = _number;
    json[json::DATE] = _date;
    json[json::TIME] = _time;
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

  /**
   * @brief GetName
   * @return константную ссылку на имя
   */
  const QString& GetName() const noexcept { return _name; }
  /**
   * @brief GetId
   * @return константную ссылку на айди
   */
  const QString& GetId() const noexcept { return _id; }
  /**
   * @brief GetNumber
   * @return  константную ссылку на номер
   */
  const QString& GetNumber() const noexcept { return _number; }
  /**
   * @brief GetDate
   * @return константную ссылку на дату
   */
  const QString& GetDate() const noexcept { return _date; }
  /**
   * @brief GetTime
   * @return константную ссылку на время
   */
  const QString& GetTime() const noexcept { return _time; }

 private:
  QString _name;    // json: "name"
  QString _id;      // json: "id"
  QString _number;  // json: "number"
  QString _date;    // json: "date"
  QString _time;    // json: "time"
};
}  // namespace test

#endif  // CLIENTSERVERQT_COMMON_DATA_H_
