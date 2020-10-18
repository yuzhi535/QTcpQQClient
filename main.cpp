#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Dialog* dialog = new Dialog();
    dialog->show();
    return a.exec();
}
