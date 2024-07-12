#include "Request.hpp"

#include <QDBusConnection>
#include <QDBusMessage>

#include <iostream>

void Request::sendErrorResponse(const QString& msg) const {
    QDBusMessage response_msg =
        this->_msg.createErrorReply(QDBusError::NotSupported, msg);
    response_msg << msg;
    QDBusConnection::sessionBus().send(response_msg);
}

void Request::sendSuccessResponse() const {
    QDBusMessage response_msg = this->_msg.createReply();
    QString str = "Ok";
    response_msg << QVariant::fromValue(str);
    QDBusConnection::sessionBus().send(response_msg);
}