#ifndef SHARE_SERVICE_H
#define SHARE_SERVICE_H

#include <QCoreApplication>
#include <QDBusVariant>
#include <QObject>
#include <QString>

#include <iostream>

class ShareService : public QObject {
    Q_OBJECT

  public slots:
    QString RegisterService(QString name, QStringList supportedFormats);
    QString OpenFile(QString path);
    QString OpenFileUsingService(QString path, QString service);

  private:
    std::map<QString, std::vector<QString>> formatToService;
    std::map<QString, QStringList> serviceToFormats;

    QString GetFileFormat(QString filename);
};

#endif // SHARE_SERVICE_H