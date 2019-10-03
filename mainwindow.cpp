#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
}

MainWindow::~MainWindow()
{
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
