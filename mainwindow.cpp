#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("主界面"));
    qwidget = new QWidget(this);
    this->setCentralWidget(qwidget);
    grid = new QGridLayout(qwidget);
    list_1 = new QListWidget(this);
    view = new QGraphicsView(this);
    button_1 = new QPushButton(this);
    button_2 = new QPushButton(this);
    button_3 = new QPushButton(this);
    button_4 = new QPushButton(this);
    button_1->setAccessibleName("button_1");
    button_2->setAccessibleName("button_2");
    button_3->setAccessibleName("button_3");
    button_4->setAccessibleName("button_4");

    text = new QTextEdit(this);

    button_1->setText(QString(tr("发送")));
    button_2->setText(QString(tr("关闭")));
    button_3->setText(QString(tr("选择图片")));
    button_4->setText(QString(tr("发送图片")));
    button_1->setShortcut(QString("ctrl+return"));
    button_2->setShortcut(QString("esc"));
    connect(button_2, &QPushButton::clicked, this, &MainWindow::close);
    connect(button_1, &QAbstractButton::clicked, this, &MainWindow::on_button_1_clicked);
    connect(button_3, &QAbstractButton::clicked, this, &MainWindow::on_button_3_clicked);
    connect(button_4, &QAbstractButton::clicked, this, &MainWindow::on_button_4_clicked);

    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(16);
    grid->addWidget(button_1, 14, 4, 2, 2);
    grid->addWidget(button_2, 14, 6, 2, 2);
    grid->addWidget(list_1, 0, 0, 10, 8);
    grid->addWidget(view, 0, 8, 16, 12);
    grid->addWidget(text, 10, 0, 4, 8);
    grid->addWidget(button_3, 14, 0, 2, 2);
    grid->addWidget(button_4, 14, 2, 2, 2);

    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSocket(MyTcpClient *& client)
{
    myClient = client;
}

QString MainWindow::intToString(int num)
{
    QString re;
    while (num)
    {
        re = (char)(num % 10) + 48 + re;
        num /= 10;
    }
    return re;
}

void MainWindow::createFile(QByteArray& data, QString suffix)
{
    QString th = myClient->getName();
    th = QString("/") + th;
    QString path = QDir::currentPath() + th;   //存储到本地文件夹
    path = QDir::toNativeSeparators(path);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    QTime time(QTime::currentTime());
    QString curr = intToString(QTime(0, 0, 0).secsTo(time));
    curr = "/" + curr;
    QString name(path + curr + suffix);
    QFile file;                                  //创建新文件
    name = QDir::toNativeSeparators(name);
    file.setFileName(name);
    file.open(QIODevice::ReadOnly);
    if (!file.exists())
    {
        file.close();
        file.open(QIODevice::ReadWrite);
    }
    if (file.isOpen())
    {
        file.write(data);
        file.close();
    }
}

void MainWindow::addInfo()
{
    QByteArray data = myClient->readAll();
    if (!data.isNull())
    {
        QString str = data;
        if (str.at(0) != '\r')
        {
            str.remove('\b');
            list_1->addItem(str);
            createFile(data, "txt");
        }
        else if (str.at(0) == '\r')
        {
            int size = 0;
            for (int i = 1; i < data.size() && data.at(i) != '\r'; ++i)
            {
                size = size * 10 - '0' + data.at(i);
            }
            qDebug() << size;
            data.clear();
            QThread::msleep(100);
            bool flag = true;
            QTime time(QTime::currentTime());
            while (size > data.size())
            {
                data += myClient->readAll();
                if (time.secsTo(QTime::currentTime()) > 3)
                {
                    QMessageBox::information(this, QString("通知"), QString("<h1>图片接收失败</h1>"));
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                QMessageBox::information(this, QString("通知"), QString("<h1>您收到一张图片</h1>"));
                //创建文件
                createFile(data, ".png");
                showImg(data);
            }
        }
    }

}

void MainWindow::on_button_1_clicked()
{
    QString str = text->toPlainText();
    qDebug() << str;
    myClient->write(str.toUtf8());
}

void MainWindow::warn()
{
    QMessageBox::warning(this, QString("警告"), "<h1>连接中断！即将退出</h1>");
    close();
    exit(0);
}

void MainWindow::on_button_3_clicked()
{
    auto file = QFileDialog::getOpenFileName(this, tr("选择图片"), "../", tr("images(*.png)"));
    if (!file.isEmpty())
    {
        img.load(file);
        QBuffer buffer;
        buffer.open(QIODevice::ReadWrite);
        img.save(&buffer, "JPG");

        QByteArray dataArray;
        dataArray.append(buffer.data());

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(img);
        view->setScene(scene);
        view->show();
        flag = true;
    }
}

void MainWindow::showImg(QByteArray data)
{
    img.loadFromData(data, "JPG");
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    img.save(&buffer, "PNG");                 //在buffer中存储这个图片，后缀是.png

    QByteArray dataArray;
    dataArray.append(buffer.data());

    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(img);
    view->setScene(scene);
    view->show();
}

void MainWindow::on_button_4_clicked()
{
    if (flag)
    {
        if (myClient->state() == myClient->ConnectedState)
        {
            QByteArray datArray;
            QPixmap tmp = img;
            QBuffer buffer(&datArray);
            buffer.open(QIODevice::ReadWrite);
            tmp.save(&buffer, "PNG");                //做到PNG格式的传输
            auto len = datArray.size();
            QByteArray s;
            while (len)                             //先发送图片大小，让服务端做好准备
            {
                s = (char)(len % 10 + 48) + s;
                len /= 10;
            }
            s.insert(0, '\r');
            s.append('\r');

            myClient->write(s);
            datArray.append(buffer.data());
            myClient->write(datArray);
        }
        else
        {
            QMessageBox::warning(this, "警告", "<h1>没有任何有效的连接！</h1><h2>无法发送图片</h2>");
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "<h1>您还没有选择任何图片</h1>");
    }
}
