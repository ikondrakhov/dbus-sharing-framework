#include "ShareService.hpp"

#include <QtDBus/QtDBus>
#include <iostream>

ShareService::ShareService() {}

QString ShareService::RegisterService(QString name,
                                      QStringList supportedFormats) {
  std::cout << "Formats:" << std::endl;
  for (const QString &format : supportedFormats) {
    this->formatToService[format].push_back(name);
    std::cout << format.toStdString() << std::endl;
  }
  this->serviceToFormats[name] = supportedFormats;
  std::cout << "Registered service with name: " << name.toStdString()
            << std::endl;
  return "register service";
}

QString ShareService::OpenFile(QString path) {
  QString fileFormat = this->GetFileFormat(path);
  std::cout << fileFormat.toStdString() << std::endl;
  const auto &services = this->formatToService[fileFormat];
  if (services.size() == 0) {
    return "Error: No service to open file with format";
  }
  return this->OpenFileUsingService(path, services[0]);
}

QString ShareService::OpenFileUsingService(QString path, QString service) {
  QDBusInterface serviceInterface(service, "/");
  QString fileFormat = this->GetFileFormat(path);
  for (const QString &format : this->serviceToFormats[service]) {
    if (format == fileFormat) {
      QDBusReply<QString> response = serviceInterface.call("OpenFile", path);
      if (response.isValid()) {
        return "Ok";
      } else {
        return QString("Error opening file with service: ") + service;
      }
    }
  }
  return "Error opening file with service";
}

QString ShareService::GetFileFormat(QString path) {
  return path.right(path.length() - path.lastIndexOf('.') - 1);
}