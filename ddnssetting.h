#ifndef DDNSSETTING_H
#define DDNSSETTING_H

#include <QSettings>
#include <QFileInfo>
#include <QString>
#include <QApplication>

class DDnsSetting
{
public:
    DDnsSetting();
    QString getValue(QString key);
    QString setValue(QString key, QString value);
    
private:
    QSettings *config;
};

#endif // DDNSSETTING_H
