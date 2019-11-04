#ifndef DNSAPI_H
#define DNSAPI_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//template<class T1>
class DnsApi : public QObject
{
    Q_OBJECT
public:
    DnsApi(QString TOKEN_ID, QString TOKEN, QString DOMAIN);
    int changeRecord(QString record_id, QString sub_domain, QString record_type, QString value);
    QString TOKEN_ID = "";
    QString TOKEN = "";
    QString DOMAIN = "";
    ~DnsApi();
private:
    int waited_for_return = 0;
    QNetworkAccessManager *netManager;
    
private slots:
    void _getReturn(QNetworkReply *reply);
    
public: signals:
    void getReturn(QNetworkReply* reply);
};

#endif // DNSAPI_H
