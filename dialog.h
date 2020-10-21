#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "mainwindow.h"
#include <QFile>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_toolButton_clicked();

private:
    Ui::Dialog *ui;
    MainWindow* w;
//    Register* register;
};

#endif // DIALOG_H
