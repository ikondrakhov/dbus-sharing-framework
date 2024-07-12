#ifndef SHARE_SERVICE_H
#define SHARE_SERVICE_H

#include <QCoreApplication>
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
      int argc, char **argv, std::string serviceName,
      std::vector<std::string> supportedFormats,
      std::function<void(const std::string &, const Request &)> callback);

  int start();

public slots:
  QString OpenFile(QString path);

private:
  std::function<void(const std::string &, const Request &)> callback;
  QCoreApplication app;
};

#endif // SHARE_SERVICE_H