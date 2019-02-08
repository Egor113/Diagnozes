#include "mainwindow.h"
#include <QApplication>

#include "dia.h"
#include "graph.h"
#include "graphicsform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    w.showMaximized();
    w.show();

//    Dia *



    return a.exec();
}
