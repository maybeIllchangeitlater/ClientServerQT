#ifndef CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
#define CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_

#include <QJsonDocument>
#include <QJsonObject>

#include "../service/binaryService.h"
#include "../service/jsonService.h"
#include "../service/stringService.h"
#include "../service/viewService.h"

namespace test {
/**
 * @brief The Controller class предоставляющий функциональность для записи и
 * получения данных из базы данных
 */
class Controller {
 public:
  /**
   * @brief Controller конструктор принимающий в себя два объекта сервисов
   * @param stringService объект для обработки json даты
   * @param jsonService объект для обработки строковой даты
   * @param binaryService объект для обработки бинарных файлов
   * @param viewService объект для обработки view
   */
  explicit Controller(StringService &stringService, JsonService &jsonService,
                      BinaryService &binaryService, ViewService &viewService)
      : _stringService(stringService),
        _jsonService(jsonService),
        _binaryService(binaryService),
        _viewService(viewService) {}
  /**
   * @brief postString записать строку в репозиторий
   * @param data запрос
   * @return ответ
   */
  QByteArray postString(const QByteArray &data) {
    _stringService.postString(data);
    return "";
  }
  /**
   * @brief postJson записать json в репозиторий
   * @param data запрос
   * @return ответ
   */
  QByteArray postJson(const QByteArray &data) {
    _jsonService.postJson(data);
    return "";
  }
  /**
   * @brief postBinary записать бинарный файл в репозиторий
   * @param data запрос
   * @return ответ
   */
  QByteArray postBinary(const QByteArray &data) {
    _binaryService.postBinary(data);
    return "";
  }
  /**
   * @brief getMessageCount получить количество сообщений отправленных серверу
   * за все время
   * @return количество сообщений
   */
  QByteArray getMessageCount() {
    size_t stringCount = _stringService.getStringCount();
    size_t jsonCount = _jsonService.getJsonCount();
    size_t binaryCount = _binaryService.getBinaryCount();
    return QByteArray::number(stringCount + jsonCount + binaryCount);
  }
  /**
   * @brief getView получить view из базы данных
   * @return QByteArray репрезентацию view
   */
  QByteArray getView() { return _viewService.getView(); }

 private:
  StringService &_stringService;
  JsonService &_jsonService;
  BinaryService &_binaryService;
  ViewService &_viewService;
};
}  // namespace test

#endif  // CLIENTSERVERQT_SERVER_CONTROLLER_CONTROLLER_H_
