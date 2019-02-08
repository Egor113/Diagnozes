#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include "warehouse.h"
#include "worker.h"
#include "wordranger.h"
#include "worddsranger.h"
#include "dia.h"
#include "graphicsform.h"
#include "chainranger.h"
#include "chaindsranger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_item(nullptr)
{
    ui->setupUi(this);
    m_item = Q_NULLPTR;
    QObject::connect(ui->exitButton, &QPushButton::pressed, this, &MainWindow::close);
    QObject::connect(ui->b_wordRate, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_wordRateDs, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_expRate, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_expRateDs, &QPushButton::pressed, this, &MainWindow::openFile);
    QObject::connect(ui->b_Dia, &QPushButton::pressed, this, &MainWindow::showdia);

    QObject::connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

//    qRegisterMetaType< QVector<int> >("QVector<int>");
//    qRegisterMetaType< QItemSelection > ("QItemSelection");
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
    else if (sen == ui->b_expRate)
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = new Chainranger();
        w->setFileName(fileName);
        w->setTable(ui->tableWidget);
        w->start();
    }
    else if (sen == ui->b_expRateDs)
    {
        QString fileName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");

        auto w = new Chaindsranger();
        w->setFileName(fileName);
        w->setTable(ui->tableWidget);
        w->start();
    }
}

void MainWindow::showdia()
{
    if (!m_item || ui->tableWidget->columnCount() != 3)
        return;

    QString text;
    QVector<int> vec;
    QStringList list;

    if (m_item->column() != 1)
        m_item = ui->tableWidget->item(m_item->row(), 1);

    text = m_item->data(Qt::DisplayRole).toString();
    for (int i = 0 ; i < ui->tableWidget->rowCount(); i++)
    {
        if (text.compare(ui->tableWidget->item(i, 1)->data(0).toString()) == 0)
        {
            vec.append(ui->tableWidget->item(i, 2)->data(0).toInt());
            list.append(ui->tableWidget->item(i, 0)->data(0).toString());
        }
    }

    GraphicsForm * form = new GraphicsForm();
    form->setAttribute(Qt::WA_DeleteOnClose);
    QSize screenSize = qApp->desktop()->screen()->size();
    form->setMinimumSize(screenSize.width()/2, screenSize.height()/2);
    form->show();

    QObject::connect(this, &MainWindow::dataReady, form, &GraphicsForm::setGraphData);
    QObject::connect(this, &MainWindow::wordReady, form, &GraphicsForm::setGraphWord);

    emit wordReady(text);
    emit dataReady(vec, list);
}

void MainWindow::onCellClicked(int row, int column)
{
    m_item = ui->tableWidget->item(row, column);
}

