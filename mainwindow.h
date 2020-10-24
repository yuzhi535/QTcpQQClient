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
#include <QMessageBox>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>


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
    void warn();
    void on_button_3_clicked();
    void on_button_4_clicked();



private:
    Ui::MainWindow *ui;
    QWidget* qwidget;
    QListWidget* list_1;
    QGraphicsView* view;
    QTextEdit* text;
    QPushButton* button_1;
    QPushButton* button_2;
    QPushButton* button_3;
    QPushButton* button_4;
    QProgressBar* progressBar;
    QGridLayout* grid;

    QPixmap img;

    MyTcpClient* myClient;

    bool flag;

};
#endif // MAINWINDOW_H
