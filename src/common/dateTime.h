#ifndef CLIENTSERVERQT_CLIENT_UTILITY_DATETIME_H_
#define CLIENTSERVERQT_CLIENT_UTILITY_DATETIME_H_

#include <QString>

namespace test {
struct DateTime {
  /**
   * @brief getDateTime получить текущую дату и время
   * @return пару из строк - дата и время
   */
  static std::pair<QString, QString> getDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    auto localized = *std::localtime(&currentTime);
    auto date = QString::number(localized.tm_year + 1900) + "-" +
                QString::number(localized.tm_mon + 1) + "-" +
                QString::number(localized.tm_mday);

    auto time = QString::number(localized.tm_hour) + ":" +
                QString::number(localized.tm_min) + ":" +
                QString::number(localized.tm_sec);
    return std::make_pair(std::move(date), std::move(time));
  }
};
}  // namespace test

#endif  // CLIENTSERVERQT_CLIENT_UTILITY_DATETIME_H_
