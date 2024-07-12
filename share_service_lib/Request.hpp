#ifndef REQUEST_H
#define REQUEST_H

#include <QDBusMessage>
#include <QString>

class Request {
  public:
    Request(QDBusMessage msg) : _msg(msg){};
    virtual void sendErrorResponse(const QString& msg) const;
    virtual void sendSuccessResponse() const;

  private:
    QDBusMessage _msg;
};

#endif // REQUEST_H