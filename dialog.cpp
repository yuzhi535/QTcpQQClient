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
    socket->setReadBufferSize(0);
    w->setSocket(socket);

}

#include <iostream>
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sleep(qint32 sec)
{
    QTime time1 = QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < time1)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Dialog::on_pushButton_clicked()
{
    socket->setReadBufferSize(0);
    socket->connectToHost(QHostAddress(ip), port);
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


            QString name = ui->lineEdit->text();
            socket->setName(name);

            QString login("\b");
            login += name + "\b";
            login += ui->lineEdit_2->text();
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

void Dialog::setIp(QString _ip)
{
    ip = _ip;
}

void Dialog::setPort(qint32 _port)
{
    port = _port;
}

#ifdef ADD
void Dialog::showEvent(QShowEvent* )
{

}

void Dialog::closeEvent(QCloseEvent* e)
{
    if (!animation)
    {
        qDebug() << "close!";
        animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(1);
        animation->setEndValue(0);

        connect(animation, SIGNAL(finished()), SLOT(show()));
        animation->start();
        e->ignore();
    }
    else
    {
        delete animation;
        animation = nullptr;
        exit(0);
    }
}
#endif
