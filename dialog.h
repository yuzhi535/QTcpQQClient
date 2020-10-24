#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "mainwindow.h"
#include <QFile>
#include "mytcpclient.h"
#include <QTime>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void sleep(qint32 sec);

signals:
    void newMsg(QString msg);

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    MainWindow* w;               //主界面
    MyTcpClient* socket;          //connect
    QString ip = "127.0.0.1";    //ip
    qint32 port = 18080;          //port
};

#endif // DIALOG_H
