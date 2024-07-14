#include "ShareService.hpp"

#include <QtDBus/QtDBus>
#include <iostream>

QString ShareService::RegisterService(QString name,
                                      QStringList supportedFormats) {
    for (const QString& format : supportedFormats) {
        this->formatToService[format].push_back(name);
    }
    this->serviceToFormats[name] = supportedFormats;
    std::cout << "Registered service with name: " << name.toStdString()
              << std::endl;
    return "register service";
}

QString ShareService::OpenFile(QString path) {
    QString fileFormat = this->GetFileFormat(path);
    std::cout << fileFormat.toStdString() << std::endl;
    const auto& services = this->formatToService[fileFormat];
    if (services.size() == 0) {
        return QString("Error: No service to open file with format %1")
            .arg(fileFormat);
    }
    return this->OpenFileUsingService(path, services[0]);
}

QString ShareService::OpenFileUsingService(QString path, QString service) {
    QDBusInterface serviceInterface(service, "/");
    QString fileFormat = this->GetFileFormat(path);
    for (const QString& format : this->serviceToFormats[service]) {
        if (format == fileFormat) {
            QDBusReply<QString> response =
                serviceInterface.call("OpenFile", path);
            if (response.isValid()) {
                return response.value();
            } else {
                return QString("Error opening file with service: %1 %2")
                    .arg(service, response.error().message());
            }
        }
    }
    return QString("No service with name %1 found").arg(service);
}

QString ShareService::GetFileFormat(QString path) {
    return path.right(path.length() - path.lastIndexOf('.') - 1);
}