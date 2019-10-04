#ifndef DDNSLOOP_H
#define DDNSLOOP_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include "ddnssetting.h"
#include <QObject>
#include <QNetworkInterface>
#include <QDebug>
class DDnsLoop: public QThread
{
    Q_OBJECT
public:
    DDnsLoop(DDnsSetting *setting);
    DDnsSetting *setting;
    int stop_run = 1;
    QString IPAdress = "127.0.0.1";
    QString getHostIP();
signals:
    void postdata();
protected:
    void run() override;
    QNetworkAccessManager* naManager;
};

#endif // DDNSLOOP_H
