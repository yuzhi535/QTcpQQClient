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
    list_2 = new QListWidget(this);
    list_3 = new QListWidget(this);
    button_1 = new QPushButton(this);
    button_2 = new QPushButton(this);
    text = new QTextEdit(this);

    button_1->setText(QString(tr("发送")));
    button_2->setText(QString(tr("关闭")));
    button_1->setShortcut(QString("return"));
    button_2->setShortcut(QString("esc"));
    connect(button_2, &QPushButton::clicked, this, &MainWindow::close);
    connect(button_1, &QAbstractButton::clicked, this, &MainWindow::on_button_1_clicked);

    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(16);
    grid->addWidget(button_1, 14, 13, 2, 2);
    grid->addWidget(button_2, 14, 11, 2, 2);
    grid->addWidget(list_1, 0, 0, 10, 16);
    grid->addWidget(list_2, 10, 16, 6, 4);
    grid->addWidget(list_3, 0, 16, 10, 4);
    grid->addWidget(text, 10, 0, 4, 16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSocket(MyTcpClient *& client)
{
    myClient = client;
}

void MainWindow::addInfo()
{
    QString str = myClient->readAll();
    list_1->addItem(str);
}

void MainWindow::on_button_1_clicked()
{
    QString str = text->toPlainText();
    qDebug() << str;
    myClient->write(str.toUtf8());
}
