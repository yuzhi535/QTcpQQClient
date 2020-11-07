#include "dialog.h"
#include <QApplication>
#include "form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#define MYDEBUG
#ifdef MYDEBUG
    Dialog dialog;
    dialog.show();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
