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
    QCheckBox *StatusBox;
    DDnsSetting *setting;
    Ui::MainWindow *ui;
    QString getHostIP();
    
private slots:
    void changeSetting();
};

#endif // MAINWINDOW_H
