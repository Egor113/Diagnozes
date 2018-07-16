#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "warehouse.h"
#include "worker.h"

#include "wordranger.h"
#include "worddsranger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_item(nullptr)
{
    ui->setupUi(this);

    QObject::connect(ui->exitButton, &QPushButton::pressed, this, &MainWindow::close);
    QObject::connect(ui->b_wordRate, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_wordRateDs, &QPushButton::pressed, this, &MainWindow::openFile);

    qRegisterMetaType< QVector<int> >("QVector<int>");
    qRegisterMetaType< QItemSelection > ("QItemSelection");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    auto sen = QObject::sender();
    //Возвращает указатель на объект, сигнала кот. мы попали в этот метод
    if (sen == ui->b_wordRate) //Если нажата кнопка "Определить частоту повторения слов"
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = new Wordranger();
//        QThread * thread = new QThread;
        w->setFileName(fileName);
        w->setTable(ui->tableWidget);
//        w->moveToThread(thread);

//        QObject::connect(thread, &QThread::started, w, &Wordranger::start);
//        QObject::connect(w, &Wordranger::finished, thread, &QThread::quit);

//        thread->start(QThread::HighestPriority);
        w->start();
    }
    else if (sen == ui->b_wordRateDs)
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = new WordDsRanger();
        w->setFileName(fileName);
        w->setTable(ui->tableWidget);
        w->start();
    }
}
