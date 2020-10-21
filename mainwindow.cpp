#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qwidget = new QWidget(this);
    this->setCentralWidget(qwidget);
    grid = new QGridLayout(qwidget);
    list_1 = new QListWidget(this);
    list_2 = new QListWidget(this);
    list_3 = new QListWidget(this);
    button_1 = new QPushButton(this);
    button_2 = new QPushButton(this);
    button_1->setText(QString(tr("发送")));
    button_2->setText(QString(tr("关闭")));
    connect(button_2, &QPushButton::clicked, this, &MainWindow::close);


    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(16);
    grid->addWidget(button_1, 14, 13, 2, 2);
    grid->addWidget(button_2, 14, 11, 2, 2);
    grid->addWidget(list_1, 0, 0, 10, 16);
    grid->addWidget(list_2, 10, 16, 6, 4);
    grid->addWidget(list_3, 0, 16, 10, 4);
    qwidget->setStyleSheet(QString("background: green"));
    qDebug() << grid->rowCount();
    qDebug() << grid->columnCount();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    this->show();
}

