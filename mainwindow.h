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
#include <QMessageBox>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QThread>
#include <QDate>
#include <QThread>
#include <QMutex>
#include <QRegularExpression>
#include <QMap>
#include <QSound>
#include <QListWidgetItem>

#include "mytcpclient.h"
#include "screenwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * @note the main wodow to show the chat info
 * @todo the bubble tip
 * @warning none
 * @date 2020.10.18
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSocket(MyTcpClient*& client);
    void createFile(QByteArray& data, QString suffix);
    QString intToString(int num);
    void showImg(QByteArray& img);
    void parseName(QString& msg);


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
    QListWidget* list_2;
    QGraphicsView* view;
    QTextEdit* text;
    QPushButton* button_1;
    QPushButton* button_2;
    QPushButton* button_3;
    QPushButton* button_4;
    QGridLayout* grid;     //main layout

    QPixmap img;

    MyTcpClient* myClient = nullptr;

    bool flag;     //decide whether to show the image

    QMap<QString, int> users;    //record users

    QMenu* menu;
    QAction* about;
    QMenu* screenShot;
    QAction* shot;
    QAction* hideShot;

    QMutex* mutex;   //lock and unlock

};
#endif // MAINWINDOW_H
