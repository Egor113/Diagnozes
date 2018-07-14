#include "mainwindow.h"
#include <QApplication>

#include "dia.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.showMaximized();
    w.show();

//    Dia * d = new Dia();
//    d->show();

    return a.exec();
}
