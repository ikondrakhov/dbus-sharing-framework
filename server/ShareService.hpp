#ifndef SHARE_SERVICE_H
#define SHARE_SERVICE_H

#include <QCoreApplication>
#include <QDBusVariant>
#include <QObject>
#include <QString>

#include <iostream>

class ShareService : public QObject {
  Q_OBJECT

public:
  ShareService();

public slots:
  QString RegisterService(std::string name, std::vector<std::string> supportedFormats);
  QString OpenFile(QString path);
  QString OpenFileUsingService(std::string path, std::string service);

private:
    std::map<std::string, std::vector<std::string>> formatToService;
};

#endif // SHARE_SERVICE_H