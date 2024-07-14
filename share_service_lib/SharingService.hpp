#ifndef SHARE_SERVICE_H
#define SHARE_SERVICE_H

#include <QCoreApplication>
#include <QDBusMessage>
#include <QDBusVariant>
#include <QObject>
#include <QString>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Request.hpp"

class SharingService : public QObject {
    Q_OBJECT

  public:
    SharingService(
        std::string serviceName, std::vector<std::string> supportedFormats,
        std::function<void(const std::string&, const Request&)> callback,
        int argc = 0, char* argv[] = nullptr);

    int start();

  public slots:
    void OpenFile(QString path, const QDBusMessage& msg);

  private:
    std::function<void(const std::string&, const Request&)> callback;
    QCoreApplication app;
};

#endif // SHARE_SERVICE_H