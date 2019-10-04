#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setting = new DDnsSetting ();
    this->setWindowTitle("ink19 DDns");
    
    QGridLayout *mlayout = new QGridLayout () ;
    QLabel *text;
    
    text = new QLabel("ID");
    IDEdit = new QLineEdit;
    mlayout->addWidget(text, 1, 1);
    mlayout->addWidget(IDEdit, 1, 2);
    
    text = new QLabel("Token");
    TokenEdit = new QLineEdit;
    mlayout->addWidget(text, 2, 1);
    mlayout->addWidget(TokenEdit, 2, 2);
    
    text = new QLabel("Domain");
    DomainEdit = new QLineEdit;
    mlayout->addWidget(text, 3, 1);
    mlayout->addWidget(DomainEdit, 3, 2);
    
    text = new QLabel("Record Id");
    RecordIdEdit = new QLineEdit;
    mlayout->addWidget(text, 4, 1);
    mlayout->addWidget(RecordIdEdit, 4, 2);
    
    text = new QLabel("Sub Domain");
    SubDomainEdit = new QLineEdit;
    mlayout->addWidget(text, 5, 1);
    mlayout->addWidget(SubDomainEdit, 5, 2);
    
    QPushButton *changeButton = new QPushButton ("Change");
    mlayout->addWidget(changeButton, 6, 1);
    
    QHBoxLayout *choose = new QHBoxLayout;
    text = new QLabel("开始");
    StatusBox = new QCheckBox;
    choose->addWidget(text);
    choose->addWidget(StatusBox);
    mlayout->addLayout(choose, 6, 2);
    
    text = new QLabel("IP:");
    mlayout->addWidget(text, 7, 1);
    
    IPLabel = new QLabel(this->getHostIP());
    mlayout->addWidget(IPLabel, 7, 2);
    
    text = new QLabel("Status:");
    mlayout->addWidget(text, 8, 1);
    
    StatusLable = new QLabel("Successful");
    mlayout->addWidget(StatusLable, 8, 2);
    
    
    //初始化值
    this->IDEdit->setText(this->setting->getValue("ID"));
    this->TokenEdit->setText(this->setting->getValue("Token"));
    this->DomainEdit->setText(this->setting->getValue("domain"));
    this->RecordIdEdit->setText(this->setting->getValue("record_id"));
    this->SubDomainEdit->setText(this->setting->getValue("sub_domain"));
    if(this->setting->getValue("status") == "enable") {
        this->StatusBox->setCheckState(Qt::CheckState::Checked);
    } else {
        this->StatusBox->setCheckState(Qt::CheckState::Unchecked);
    }
    
    connect(changeButton, SIGNAL(clicked()), this, SLOT(changeSetting()));
    naManager = new QNetworkAccessManager(this);
    connect(naManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(netReply(QNetworkReply *)));
    this->loop = new DDnsLoop(this->setting);
    
    connect(this->loop, SIGNAL(postdata()), this, SLOT(sendData()));
    this->loop->stop_run = 0;
    this->loop->start();
    
    QWidget *mainw = new QWidget(this);
    mainw->setLayout(mlayout);
    this->setCentralWidget(mainw);
}

MainWindow::~MainWindow()
{
    delete this->setting;
    this->loop->stop_run = 1;
    this->loop->wait();
    delete this->loop;
    delete ui;
}

QString MainWindow::getHostIP()
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

void MainWindow::changeSetting()
{
    this->setting->setValue("ID", this->IDEdit->text());
    this->setting->setValue("Token", this->TokenEdit->text());
    this->setting->setValue("domain", this->DomainEdit->text());
    this->setting->setValue("record_id", this->RecordIdEdit->text());
    this->setting->setValue("sub_domain", this->SubDomainEdit->text());
    this->setting->setValue("status", this->StatusBox->isChecked()?"enable":"disable");
}

void MainWindow::changeStatus(QString IPAddress, bool status)
{
    this->IPLabel->setText(IPAddress);
    this->StatusLable->setText(status?"Successful":"False");
}

void MainWindow::sendData()
{
    QNetworkRequest request(QUrl("https://dnsapi.cn/Record.Modify"));
    QByteArray postArray;
    postArray.append("login_token=" + this->setting->getValue("ID") + "," + this->setting->getValue("Token"));
    postArray.append("&format=json");
    postArray.append("&lang=cn");
    postArray.append("&domain=" + this->setting->getValue("domain"));
    postArray.append("&record_id=" + this->setting->getValue("record_id"));
    postArray.append("&sub_domain=" + this->setting->getValue("sub_domain"));
    postArray.append("&record_type=" + this->setting->getValue("record_type"));
    postArray.append("&record_line=%e9%bb%98%e8%ae%a4");
    postArray.append("&value=" + getHostIP());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader,postArray.size());
    request.setHeader(QNetworkRequest::UserAgentHeader, "ink19 DDns/0.1 ink19@qq.com");
    naManager->post(request, postArray);
}

void MainWindow::netReply(QNetworkReply *replay)
{
    bool status = false;
    QString IPaddress;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replay->readAll()));
    if(jsonDoc.object().take("status").toObject().take("code").toString() == "1") {
        status = true;
        IPaddress = jsonDoc.object().take("record").toObject().take("value").toString();
        this->loop->IPAdress = IPaddress;
    } else {
        IPaddress = "Error";
    }
    changeStatus(IPaddress, status);
}
