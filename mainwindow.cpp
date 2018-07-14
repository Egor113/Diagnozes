#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "warehouse.h"
#include "worker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->b_wordRate, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_wordRateDs, &QPushButton::pressed, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    auto sen = QObject::sender();
    if (sen == ui->b_wordRate)
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = WareHouse::analise(WareHouse::Word, fileName);
        w->setTable(ui->tableWidget);
        w->start();
    }
    else if (sen == ui->b_wordRateDs)
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = WareHouse::analise(WareHouse::WordDs, fileName);
        w->setTable(ui->tableWidget);
        w->start();
    }
}
