#include "dnsapi.h"

//template<class T1>
//int DnsApi<T1>::changeRecord(QString record_id, QString sub_domain, QString record_type, QString value, void (T1::*func_call_back)(QNetworkReply *reply))
//{
//    if(this->waited_for_return == 1)
//        return 1;
//    this->waited_for_return = 1;
//    QObject::connect(this->netManager, SIGNAL(finished(QNetworkReply *)), mainClass, SLOT(T1::*func_call_back(QNetworkReply*)));
//    QNetworkRequest request(QUrl("https://dnsapi.cn/Record.Modify"));
//    QByteArray postArray;
//    postArray.append("login_token=" + this->TOKEN_ID + "," + this->TOKEN);
//    postArray.append("&format=json");
//    postArray.append("&lang=cn");
//    postArray.append("&domain=" + this->DOMAIN);
//    postArray.append("&record_id=" + record_id);
//    postArray.append("&sub_domain=" + sub_domain);
//    postArray.append("&record_type=" + record_type);
//    postArray.append("&record_line=%e9%bb%98%e8%ae%a4");
//    postArray.append("&value=" + value);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//    request.setHeader(QNetworkRequest::ContentLengthHeader, postArray.size());
//    request.setHeader(QNetworkRequest::UserAgentHeader, "ink19 DDns/0.1 ink19@qq.com");
//    this->netManager->post(request, postArray);
//    return 0;
//}

//template<class T1>
//DnsApi<T1>::DnsApi(QString TOKEN_ID, QString TOKEN, QString DOMAIN, T1 *mainClass):
//    TOKEN_ID(TOKEN_ID),
//    TOKEN(TOKEN),
//    DOMAIN(DOMAIN),
//    mainClass(mainClass)
//{
//    this->netManager = new QNetworkAccessManager(this);
//}

//template<class T1>
//DnsApi<T1>::~DnsApi()
//{
//    delete  this->netManager;
//}



DnsApi::DnsApi(QString TOKEN_ID, QString TOKEN, QString DOMAIN):
    TOKEN_ID(TOKEN_ID),
    TOKEN(TOKEN),
    DOMAIN(DOMAIN)
{
    this->netManager = new QNetworkAccessManager(this);
    connect(this->netManager, SIGNAL(finished(QNetworkReply *reply)), this, SLOT(_getReturn(QNetworkReply *reply)));
}

int DnsApi::changeRecord(QString record_id, QString sub_domain, QString record_type, QString value)
{
    if(this->waited_for_return == 1)
            return 1;
    this->waited_for_return = 1;
    //QObject::connect(this->netManager, SIGNAL(finished(QNetworkReply *)), mainClass, SLOT(T1::*func_call_back(QNetworkReply*)));
    QNetworkRequest request(QUrl("https://dnsapi.cn/Record.Modify"));
    QByteArray postArray;
    postArray.append("login_token=" + this->TOKEN_ID + "," + this->TOKEN);
    postArray.append("&format=json");
    postArray.append("&lang=cn");
    postArray.append("&domain=" + this->DOMAIN);
    postArray.append("&record_id=" + record_id);
    postArray.append("&sub_domain=" + sub_domain);
    postArray.append("&record_type=" + record_type);
    postArray.append("&record_line=%e9%bb%98%e8%ae%a4");
    postArray.append("&value=" + value);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, postArray.size());
    request.setHeader(QNetworkRequest::UserAgentHeader, "ink19 DDns/0.1 ink19@qq.com");
    this->netManager->post(request, postArray);
    return 0;
}

DnsApi::~DnsApi()
{
    delete  this->netManager;
}

void DnsApi::_getReturn(QNetworkReply *reply)
{
    waited_for_return = 0;
    emit getReturn(reply);
}


