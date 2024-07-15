# DBus фреймворк для шаринга файлов

Фреймворк для обработки файлов. Сервер позволяет регистрировать и вызывать обработчик для нужного формата файла.
Бибилиотека share_service_lib позволяет создавать и регистрировать обработчики для указанных форматов.

## client

Содержит клиента, который отправляет простой запрос OpenFile на сервер

## server

Создержит сервер, который принимает 3 вида запросов:
- RegisterService(serviceName: string, supportedFormats: list<string>)
- OpenFile(path: string)
- OpenFileUsingService(filePath: string, serviceName: string)

## share_service_lib

Библиотека для взаимодействия с сервером, позволяет регестрировать сервис на сервере для обработки файлов

## share_service_lib_example

Содержит пример использования библиотеки

## Сборка

Для сборки проекта нужно запустить следующие команды:

```
mkdir build && cd build
cmake ..
make
```

После сборки будут созданы папки с сответствующими названиями
server - будет содержать файлы для запуска сервера
client - файлы для запуска клиента
share_service_lib - файлы с динамической библиотекой
share_service_lib_example - файлы с примером использования библиотеки

## Запуск примера

Для запуска примера сначала запустите сервер:
```
./server/server
```

Затем запустите пример:
```
./share_service_lib_example/share_service_lib_example
```

Для отправки запроса можно использовать gdbus:
```
gdbus call -e -d com.example.mediaplayer -o / -m com.example.mediaplayer.OpenFile /home/user/Documents/video.mp4
```
или
```
gdbus call -e -d com.system.sharing -o / -m com.system.sharing.OpenFile /home/user/Documents/video.mp4
```
