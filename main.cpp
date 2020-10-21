#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    Dialog dialog;
//    QObject::connect(&dialog, &QDialog::close, &w, &MainWindow::show);
    dialog.show();
    return a.exec();
}
