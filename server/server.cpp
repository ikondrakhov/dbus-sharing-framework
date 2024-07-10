#include <QCoreApplication>
#include <QtDBus/QtDBus>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

#define SERVICE_NAME "com.system.sharing"
#define INTERFACE_NAME "com.system.sharing"

#ifndef DAEMON_H
#define DAEMON_H

#include <QCoreApplication>
#include <QDBusVariant>
#include <QObject>
#include <QString>

#include <iostream>

class Sharer : public QObject {
  Q_OBJECT

public:
  Sharer() {

  }

public slots:
  QString RegisterService(std::string name, std::vector<std::string> supportedFormats) {
    return "register service";
  }
  QString OpenFile(QString path) {
    std::cout << path.toStdString() << std::endl;
    return QString("open file ") + path;
  }
  QString OpenFileUsingService(std::string path, std::string service) {
    return "open file using service";
  }

private:
    std::map<std::string, std::vector<std::string>> formatToService;
};

#endif // DAEMON_H

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  // Check to see if the QDBus can be connected to
  if (!QDBusConnection::sessionBus().isConnected()) {
    fprintf(stderr, "Cannot connect to the D-Bus session bus.\n");
    exit(1);
  }

  // Register our service name so that a client can use it
  if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::sessionBus().lastError().message()));
    exit(1);
  }

  Sharer daemon;

  // Register all slots so that we can access them from another application
  QDBusConnection::sessionBus().registerObject("/", INTERFACE_NAME, &daemon,
                                               QDBusConnection::ExportAllSlots);

  return app.exec();
}

#include "server.moc"