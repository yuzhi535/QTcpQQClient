#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMovie>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QProgressBar>
#include <QGridLayout>
#include "mytcpclient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSocket(MyTcpClient*& client);

signals:

public slots:
    void addInfo();
    void on_button_1_clicked();



private:
    Ui::MainWindow *ui;
    QWidget* qwidget;
    QListWidget* list_1;
    QListWidget* list_2;
    QListWidget* list_3;
    QTextEdit* text;
    QPushButton* button_1;
    QPushButton* button_2;
    QProgressBar* progressBar;
    QGridLayout* grid;

    MyTcpClient* myClient;

};
#endif // MAINWINDOW_H
