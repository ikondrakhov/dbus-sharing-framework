#include "SharingService.hpp"

#define SERVICE_NAME "com.system.sharing"

#include <QtDBus/QtDBus>
#include <iostream>

#include "Request.hpp"

SharingService::SharingService(
    int argc, char** argv, std::string serviceName,
    std::vector<std::string> supportedFormats,
    std::function<void(const std::string&, const Request&)> cb)
    : callback(cb), app(argc, argv) {

    // Check to see if the QDBus can be connected to
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n");
        exit(1);
    }

    // Register our service name so that a client can use it
    if (!QDBusConnection::sessionBus().registerService(
            QString::fromStdString(serviceName))) {
        fprintf(
            stderr, "%s\n",
            qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    // Register all slots so that we can access them from another application
    QDBusConnection::sessionBus().registerObject(
        "/", QString::fromStdString(serviceName), this,
        QDBusConnection::ExportAllSlots);

    QDBusInterface serviceInterface(SERVICE_NAME, "/");
    QVector<QString> qt;
    std::transform(supportedFormats.begin(), supportedFormats.end(),
                   std::back_inserter(qt), [](const std::string& v) {
                       return QString::fromStdString(v);
                   });
    QDBusReply<QString> response = serviceInterface.call(
        "RegisterService", QString::fromStdString(serviceName), qt.toList());
    std::cout << "success" << std::endl;
}

int SharingService::start() { return app.exec(); }

void SharingService::OpenFile(QString path, const QDBusMessage& msg) {
    Request simpleRequest(msg);
    this->callback(path.toStdString(), simpleRequest);
}