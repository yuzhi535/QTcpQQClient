#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "mainwindow.h"
#include <QFile>
#include "mytcpclient.h"
#include <QTime>
#include <QMessageBox>
#include <QPropertyAnimation>

//#define ADD

namespace Ui {
class Dialog;
}

/**
 * @brief The Dialog class
 *
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void sleep(qint32 sec);
    void setIp(QString _ip);
    void setPort(qint32 _port);

signals:
    void newMsg(QString msg);

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

#ifdef ADD
protected:
    void closeEvent(QCloseEvent * e) override;
    void showEvent(QShowEvent* e) override;
#endif

private:
    Ui::Dialog *ui;
    MainWindow* w;              //main window
    MyTcpClient* socket;        //used to connect, send and receive
    QString ip = "127.0.0.1";   //ip
    qint32 port = 18080;        //port

#ifdef ADD
    QPropertyAnimation* animation;   //implement close and open animation
#endif
};

#endif // DIALOG_H
