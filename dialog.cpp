#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    w = new MainWindow();
    register = new Risgister();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << "success";
    close();
    w->show();       //做打开的动画效果
}

void Dialog::on_pushButton_2_clicked()
{
    close();
}

void Dialog::on_toolButton_clicked()
{

}
