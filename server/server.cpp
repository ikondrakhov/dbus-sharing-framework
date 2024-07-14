#include <QCoreApplication>
#include <QtDBus/QtDBus>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

#include "ShareService.hpp"

#define SERVICE_NAME "com.system.sharing"
#define INTERFACE_NAME "com.system.sharing"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // Check to see if the QDBus can be connected to
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n");
        exit(1);
    }

    // Register our service name so that a client can use it
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        fprintf(
            stderr, "%s\n",
            qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    ShareService service;
    QDBusConnection::sessionBus().registerObject(
        "/", INTERFACE_NAME, &service, QDBusConnection::ExportAllSlots);

    return app.exec();
}