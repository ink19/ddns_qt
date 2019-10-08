#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QNetworkInterface>
#include <QList>
#include <QDebug>
#include "ddnssetting.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include "ddnsloop.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLineEdit *IDEdit;
    QLineEdit *TokenEdit;
    QLineEdit *DomainEdit;
    QLineEdit *RecordIdEdit;
    QLineEdit *SubDomainEdit;
    QLabel *IPLabel;
    QLabel *StatusLable;
    QCheckBox *StatusBox;
    DDnsSetting *setting;
    Ui::MainWindow *ui;
    QNetworkAccessManager *naManager;
    QString getHostIP();
    DDnsLoop *loop;
    QTcpServer *server;
    void changeStatus(QString IPAddress, bool status);
private slots:
    void getNewConnection();
    void changeSetting();
    void sendData();
    void netReply(QNetworkReply *replay);
};

#endif // MAINWINDOW_H
