#include <stdio.h>

#define SERVICE_NAME "com.system.sharing"

#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

#include <iostream>

int main(int argc, char **argv)
{
    QDBusInterface serviceInterface(SERVICE_NAME, "/");
    QDBusReply<QString> response = serviceInterface.call("OpenFile", "client path");
    std::cout << "success" << std::endl;
    return 1;
}