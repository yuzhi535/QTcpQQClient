#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString("登陆界面"));

    w = new MainWindow();
    socket = new MyTcpClient();
    w->setSocket(socket);
}

#include <iostream>
Dialog::~Dialog()
{
    delete ui;
    std::cout << "exit(0)" << std::endl;
}

void Dialog::sleep(qint32 sec)
{
    QTime time1 = QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < time1) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Dialog::on_pushButton_clicked()
{
    socket->connectToHost(QHostAddress(ip), port);
//    sleep(100);
    if (socket->state() == QAbstractSocket::ConnectingState)
    {
        sleep(100);
        if (socket->state() == QAbstractSocket::ConnectedState)
        {
            connect(socket, &QAbstractSocket::readyRead, w, &MainWindow::addInfo);
            connect(socket, &QAbstractSocket::disconnected, w, &MainWindow::warn);
            qDebug() << "success";
            close();
            w->show();       //做打开的动画效果

            QString login("\b");
            login += ui->lineEdit->text() + "\b";
            login += ui->lineEdit_2->text() + "\b";
            socket->write(login.toUtf8());
        }
        else
        {
            QMessageBox::warning(this, QString("警告"), QString("未连接到服务器"));
        }
    }
    else
    {
        QMessageBox::warning(this, QString("警告"), QString("未连接到服务器"));
    }
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}
