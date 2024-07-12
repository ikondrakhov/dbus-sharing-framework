#include "Request.hpp"

#include <iostream>

void Request::sendErrorResponse(const QString& msg) const {
    std::cout << msg.toStdString() << std::endl;
    /*QDBusMessage msg = QDBusMessage::createSignal( ... )
    QStringList strlist;
    strlist << "Hello" << "World";
    msg << QVariant::fromValue( strlist);
    QDBusConnection::systemBus().send( msg );*/
}

void Request::sendSuccessResponse() const { std::cout << "Ok" << std::endl; }