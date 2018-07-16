#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "warehouse.h"
#include "worker.h"
#include "wordranger.h"
#include "worddsranger.h"
#include "dia.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_item(nullptr)
{
    ui->setupUi(this);
    m_item = Q_NULLPTR;
    QObject::connect(ui->exitButton, &QPushButton::pressed, this, &MainWindow::close);
    QObject::connect(ui->b_wordRate, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_wordRateDs, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_Dia,&QPushButton::pressed, this, &MainWindow::showdia);

    qRegisterMetaType< QVector<int> >("QVector<int>");
    qRegisterMetaType< QItemSelection > ("QItemSelection");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    m_item = Q_NULLPTR;
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

void MainWindow::showdia()
{
    //if( dia != NULL) delete dia;
    dia = new Dia();
    if (!m_item || ui->tableWidget->columnCount() != 3)
        return;
    QVector <CurrWordDia> v_curr;
    QString text;

    if (m_item->column() != 1)
        m_item = ui->tableWidget->item(m_item->row(), 1);

    text = m_item->data(Qt::DisplayRole).toString();
    for (int i = 0 ; i < ui->tableWidget->rowCount(); i++)
    {
        if (text.compare(ui->tableWidget->item(i, 1)->data(0).toString()) == 0)
        {
            CurrWordDia w_curr;
            w_curr.diagID = ui->tableWidget->item(i, 0)->data(0).toString();
            w_curr.count = ui->tableWidget->item(i, 2)->data(0).toInt();
            v_curr.push_back(w_curr);
        }
    }
//  Формирование нового вектора (диагноз, кол-во повторений)
    dia->setPlotParams(text,v_curr);
    //w->setPlotParams(text,an.v_curr);
    dia->show();
}

