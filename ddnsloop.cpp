#include "ddnsloop.h"

DDnsLoop::DDnsLoop(DDnsSetting *setting):
    setting(setting)
{
    
    
}

void DDnsLoop::run()
{
    
    while (!stop_run) {
        if(this->setting->getValue("status") == "enable") {
            if(getHostIP() != this->IPAdress) {
                emit postdata();
            }
        }
        this->sleep(1);
    }
}

QString DDnsLoop::getHostIP()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(auto item : ipAddressList) {
        if(item.toIPv4Address() != 0 && item.toIPv4Address() != 2130706433) {
            strIpAddress = item.toString();
            return strIpAddress;
        }
    }
    return QHostAddress(QHostAddress::LocalHost).toString();
}
