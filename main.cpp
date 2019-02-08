#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

#include "dia.h"
#include "graph.h"
#include "graphicsform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    w.showMaximized();
    w.show();

    return a.exec();
}
