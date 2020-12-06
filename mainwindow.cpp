#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mutex = new QMutex();

    setWindowTitle(QString("主界面"));
    qwidget = new QWidget(this);
    this->setCentralWidget(qwidget);
    grid = new QGridLayout(qwidget);
    list_1 = new QListWidget(this);
    list_2 = new QListWidget(this);
    view = new QGraphicsView(this);
    text = new QTextEdit(this);
    button_1 = new QPushButton(this);
    button_2 = new QPushButton(this);
    button_3 = new QPushButton(this);
    button_4 = new QPushButton(this);
    button_1->setAccessibleName("button_1");
    button_2->setAccessibleName("button_2");
    button_3->setAccessibleName("button_3");
    button_4->setAccessibleName("button_4");

    view->setStatusTip(QString("预览图片"));
    text->setStatusTip(QString("消息框"));
    list_1->setStatusTip(QString("文本接收框"));
    list_2->setStatusTip(QString("显示群成员"));
    button_1->setText(QString(tr("发送")));
    button_2->setText(QString(tr("关闭")));
    button_3->setText(QString(tr("选择图片")));
    button_4->setText(QString(tr("发送图片")));
    button_1->setShortcut(QString("ctrl+return"));
    button_2->setShortcut(QString("esc"));

    //设置信号槽
    connect(button_2, &QPushButton::clicked, [&] () {close(); exit(0); });
    connect(button_1, &QPushButton::clicked, this, &MainWindow::on_button_1_clicked);
    connect(button_3, &QPushButton::clicked, this, &MainWindow::on_button_3_clicked);
    connect(button_4, &QPushButton::clicked, this, &MainWindow::on_button_4_clicked);
    connect(list_1, &QListWidget::doubleClicked, [&]() {
        QString msg = list_1->currentItem()->text();
        QMessageBox::information(this, QString("通知"), QString("<h2>" + msg + "</h2>"));
    });

    //设置组件位置
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(16);
    grid->addWidget(button_1, 14, 4, 2, 2);
    grid->addWidget(button_2, 14, 6, 2, 2);
    grid->addWidget(list_1, 0, 0, 10, 8);
    grid->addWidget(view, 0, 8, 12, 12);
    grid->addWidget(text, 10, 0, 4, 8);
    grid->addWidget(button_3, 14, 0, 2, 2);
    grid->addWidget(button_4, 14, 2, 2, 2);
    grid->addWidget(list_2, 12, 8, 4, 12);

    //设计组件样式
    //设计菜单
    flag = false;
    screenShot = new QMenu(this);
    menu = new QMenu(this);

    shot = new QAction(QString("截图"), this);
    about = new QAction(QString("作者"), this);
    hideShot = new QAction(QString("隐藏界面并截图"), this);

    screenShot = menuBar()->addMenu(QString("工具"));
    menu = menuBar()->addMenu(QString("关于"));

    screenShot->addAction(shot);
    screenShot->addAction(hideShot);
    menu->addAction(about);

#if 1
    connect(shot, &QAction::triggered, [&] () {
        ScreenWidget w;
        w.Instance()->showFullScreen();
        flag = true;

        QString file("screenShot.png");
        QFile testFile(file);
        if (testFile.exists())
        {
            img.load(file);
            QBuffer buffer;
            buffer.open(QIODevice::ReadWrite);
            img.save(&buffer, "png");

            QByteArray dataArray;
            dataArray.append(buffer.data());

            QGraphicsScene* scene = new QGraphicsScene();
            scene->addPixmap(img);
            view->setScene(scene);
            view->show();
        }
    });


    connect(hideShot, &QAction::triggered, [&]() {
        hide();
        QThread::msleep(1000);
        ScreenWidget w;
        w.showFullScreen();
        w.Instance()->showFullScreen();
        show();
        flag = true;

        QString file("screenShot.png");
        QFile testFile(file);
        if (testFile.exists())
        {
            img.load(file);
            QBuffer buffer;
            buffer.open(QIODevice::ReadWrite);
            img.save(&buffer, "png");

            QByteArray dataArray;
            dataArray.append(buffer.data());

            QGraphicsScene* scene = new QGraphicsScene();
            scene->addPixmap(img);
            view->setScene(scene);
            view->show();
        }
    });
#else
    connect(shot, &QAction::triggered, [&] () {
        QScreen *pscreen = QApplication::primaryScreen();
        img = pscreen->grabWindow(QApplication::desktop()->winId(), 0, 0);

        QWidget newWidget;
        newWidget.showFullScreen();

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(img);
        view->setScene(scene);
        view->show();
    });

    connect(hideShot, &QAction::triggered, [&] () {
        hide();
        QThread::msleep(1000);
        QScreen *pscreen = QApplication::primaryScreen();
        img = pscreen->grabWindow(QApplication::desktop()->winId(), 0, 0);
        show();

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(img);
        view->setScene(scene);
        view->show();

    });

#endif
    connect(about, &QAction::triggered, [&] () {
        QMessageBox::information(this, QString("通知"), QString("<h1>作者：周誉喜</h1><h2>代码已放在github上</h2><h3>"
                                                              "地址: https://github.com/yuzhi535/QTcpQQServer</h3>"));
    });

    QFile file(":/new/qss/listWidget.qss");
    if (file.exists())
    {
        file.open(QFile::ReadOnly);
        list_1->setStyleSheet(file.readAll());
        list_1->setFont(QFont("mono", 12, QFont::Bold));
        file.close();
    }
    else
    {
        QMessageBox::information(this, "通知", "not impossible");
        close();
        exit(0);
    }
    list_2->setStyleSheet("background-color: rgba(50, 50, 50, 0.6)");
    view->setStyleSheet("background-color: rgba(50, 50, 50, 0.5)");
    text->setStyleSheet("background-color: rgba(50, 50, 50, 0.8); color: rgb(255, 255, 255)");
    text->setFont(QFont("mono", 12, QFont::Bold));

    QPixmap pixmap = QPixmap(":/new/img/wallpaper.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
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
    qDebug() << th;
    th = QString("/users/") + th;
    QString path = QDir::currentPath() + th;   //存储到本地文件夹
    path = QDir::toNativeSeparators(path);
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    QString curr = QDate::currentDate().toString();
    curr = "/" + curr;
    QString name(path + curr + suffix);
    QFile file;                                  //创建新文件
    name = QDir::toNativeSeparators(name);
    file.setFileName(name);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    if (!file.exists())
    {
        file.close();
        file.open(QIODevice::ReadWrite | QIODevice::Append);
    }
    if (file.isOpen())
    {
        file.write(data + "\n");
        file.close();
    }
}

void MainWindow::parseName(QString& msg)
{
    QString name;
    for (auto i = users.begin(); i != users.end(); ++i)   //将曾经的用户标记为旧值
        i.value() = 1;
    for (int i = 1; msg.at(i) != '\r'; ++i)
    {
        if (msg.at(i) == '\b')
        {
            if (name != "" && users.find(name) == users.end())
                users.insert(name, 0);   //新用户
            else if (name != "" && users.find(name) != users.end())
                users[name] = 2;
            name = "";
        }
        else
        {
            name += msg.at(i);
        }
    }
}

void MainWindow::addInfo()
{
    static int m_flag = 0;
    QByteArray data = myClient->readAll();
    if (!data.isNull())
    {
        QString str = data;
        if (!str.isEmpty() && str.at(0) != '\r' && !m_flag)
        {
            parseName(str);

            for (auto i = users.begin(); i != users.end(); ++i)
            {
                if (i.value() == 0)
                {
                    list_2->addItem(i.key());
                    i.value() = 2;   //更新用户
                }
                if (i.value() == 1)
                {
                    for (int j = 0; j < list_2->count(); ++j)
                    {
                        if ((*list_2->item(j)).text() == i.key())
                        {
                            delete list_2->takeItem(j);   //在界面中删除无用用户
                        }
                    }
                    i = users.erase(i);   //删除离开用户
                    --i;
                }
            }

            //使用正则表达式进行删除多余部分
            str.remove(QRegularExpression(QString("\b.*\b\r")));
            str.insert(str.size(), 'a');

            list_1->addItem(str);
            createFile(data, ".txt");
            QSound::play(":/new/tip/qqSound.wav");
        }
        else if (!str.isEmpty() && (str.at(0) == '\r' || m_flag))
        {
            static QByteArray recvData;
            static int size;
            if (!m_flag)
            {
                size = data.size();;
                int i;
                for(i = 1; i < data.size() && data.at(i) != '\r'; ++i);
                size = data.mid(1, i - 1).toInt();
                qDebug() << "size=" << size;
                recvData += data.mid(i + 1);
                QByteArray& file = recvData;
                qDebug() << "filesize=" << file.size();
                if (size > recvData.size())
                {
                    ++m_flag;
                }
                else
                {
                    createFile(file, ".png");
                    showImg(file);
                    m_flag = 0;
                    size = 0;
                    recvData.clear();
                }
            }
            else
            {
                recvData += data;
                if (size > recvData.size())
                {
                    if (m_flag > 5)
                    {
                        m_flag = 0;
                        size = 0;
                        QMessageBox::information(this, QString("通知"), QString("<h1>图片接收失败</h1>"));
                        QSound::play(":/new/tip/newImg.wav");
                    }
                    else
                    {
                        ++m_flag;
                    }
                }
                else
                {
                    m_flag = 0;
                    size = 0;
                    QByteArray& file = recvData;
                    createFile(file, ".png");
                    showImg(file);
                    recvData.clear();
                }
            }
        }
    }
}

void MainWindow::on_button_1_clicked()
{
    if (myClient == nullptr)
    {
        QSound::play(":new/tip/newImg.wav");
        QMessageBox::warning(this, "错误", "不能连接到服务端，即将关闭");
        close();
        exit(0);
    }
    else if (myClient->state() == QTcpSocket::ConnectedState)
    {
        QString str = text->toPlainText();
        if (str == "")
        {
            QMessageBox::information(this, "通知", "<h2>您还未写入任何内容!</h2>");
        }
        else
        {
            myClient->write(str.toUtf8());
            text->clear();
        }
    }
    else
    {
        QMessageBox::warning(this, "错误", "不能连接到服务端，即将关闭");
        close();
        exit(0);
    }
}


void MainWindow::warn()
{
    QMessageBox::warning(this, QString("警告"), "<h1>连接中断！即将退出</h1>");
    close();
    exit(0);
}

void MainWindow::on_button_3_clicked()
{
    auto file = QFileDialog::getOpenFileName(this, tr("choose the image"), QString("."), tr("images(*.png)"));
    if (!file.isEmpty())
    {
        img.load(file);
        QBuffer buffer;
        buffer.open(QIODevice::ReadWrite);
        img.save(&buffer, "png");

        QByteArray dataArray;
        dataArray.append(buffer.data());

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(img);
        view->setScene(scene);
        view->show();
        flag = true;
    }
}

void MainWindow::showImg(QByteArray& data)
{
    mutex->lock();
    img.loadFromData(data, "PNG");
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    img.save(&buffer, "PNG");                 //在buffer中存储这个图片，后缀是.png

    QByteArray dataArray;
    dataArray.append(buffer.data());

    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(img);
    view->setScene(scene);
    view->show();
    mutex->unlock();
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
            while (len)
            {
                s = (char)(len % 10 + 48) + s;
                len /= 10;
            }
            s.insert(0, '\r');
            s.append('\r');
            s += buffer.data();
            myClient->write(s);
            myClient->waitForBytesWritten();
            flag = false;
        }
        else
        {
            QMessageBox::warning(this, "警告", "<h1>没有任何有效的连接！</h1><h2>无法发送图片</h2>");
        }
    }
    else
    {
        QSound::play(":/new/tip/newImg.wav");
        QMessageBox::warning(this, "警告", "<h1>您还没有选择任何图片</h1>");
    }
}

