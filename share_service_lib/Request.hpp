#ifndef REQUEST_H
#define REQUEST_H

#include <QString>

class Request {
  public:
    virtual void sendErrorResponse(const QString& msg) const;
    virtual void sendSuccessResponse() const;
};

#endif // REQUEST_H