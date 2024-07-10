#include "ShareService.hpp"

#include <QtDBus/QtDBus>

ShareService::ShareService() {}

QString ShareService::RegisterService(QString name,
                                      QStringList supportedFormats) {
  for (const QString &format : supportedFormats) {
    this->formatToService[format].push_back(name);
  }
  this->serviceToFormats[name] = supportedFormats;
  return "register service";
}

QString ShareService::OpenFile(QString path) {
  const auto &services = this->formatToService[this->GetFileFormat(path)];
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
      return "open file using service";
    }
  }
  return "Error opening file with service";
}

QString ShareService::GetFileFormat(QString path) {
  return path.right(path.lastIndexOf('.'));
}