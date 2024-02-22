## ClientServerQT клиенто-серверное приложение на QT

### Запуск:
- make init_sql для инициализации базы данных
- make serv для запуска сервера
- make cli для запуска клиента

### Настройки:
Сервер настраивается через конфигурационный файл /src/config.json. Все настройки для клиента доступны через GUI

### Зависимости:
- libpqxx (/src/3rdParty)
- Qt::Widget
- Qt::Network

### Функционал
Клиент с переодичностью в 1 минуту создает сессию с сервером и отправляет
- случайную строку
- структуру данных ({Имя: произвольный набор букв и цифр
ИД: произвольный набор букв и цифр
Номер: произвольный набор букв 
Дата: текущая дата
Время: текущие время
})
в виде json
- эту же структуру данных в виде бинарника

У клиента есть графический интерфейс
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/client_gui.png)
- позволяющий подключаться к серверу на другом хосте/порту
-  получать количество сообщений сохраненных в дб
-  генерировать и отправлять строки
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/stringWindow.png)
- генерировать и отправлять структуру данных
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/dataWindow.png)
- получать view из базы данных
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/viewWindow.png)
- открывать бинарные файлы содержащие структуру данных
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/binWin1.png)
![](https://github.com/maybeIllchangeitlater/ClientServerQT/blob/refactor/readmeResources/binWin2.png)

Сервер получает данные от клиента и сохранят их в базу данных
