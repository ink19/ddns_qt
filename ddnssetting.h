#ifndef DDNSSETTING_H
#define DDNSSETTING_H

#include <QSettings>
#include <QFileInfo>
class DDnsSetting
{
public:
    DDnsSetting();
private:
    QSettings *config;
};

#endif // DDNSSETTING_H
