#ifndef DDNSSETTING_H
#define DDNSSETTING_H

#include <QSettings>
#include <QFileInfo>
#include <QString>

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
