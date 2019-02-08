#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    QObject::connect(ui->btnGraph, &QPushButton::clicked, this, &Graph::printGraph);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::setGraphWord(QString word)
{
    this->word = word;
    ui->wordLabel->setText(word);
}

void Graph::setGraphData(const QVector<int> &vec, const QStringList &ds)
{
    if (vec.size() != ds.count())
        return;

    auto it1 = vec.begin();
    auto it2 = ds.begin();

    for (; it1 != vec.end(); ++it1, ++it2)
    {
        CurrWordDia word;
        word.count = (*it1);
        word.diagID = (*it2);
        v.append(word);
    }
}

void Graph::printGraph()
{
    double sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum = sum + v[i].count;
    }
    double average = sum/v.size();

    //Расчет среднеквадратичного отклонения

    sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum = sum + (v[i].count-average)*(v[i].count-average);
    }
    double deviation = sqrt(sum/(v.size()-1));

    /*!
        \brief New Paint Method
    */

    QVector<double> values;
    QVector<double> steps;      // Шаги, отставляемые по оси Х

    //Поиск наибольшего и наименьшего элемента

    double xMin = 0/*v[0].count*/, xMax = 0/*v[0].count*/, yMin = 0, yMax = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if (xMax < v[i].count) xMax = v[i].count;
        if (xMin > v[i].count) xMin = v[i].count;
    }

    double delta = (xMax- xMin)/500;

    double delta_plus = delta;

    int i = 0;

    while (delta<xMax)
    {
        values.append(gaus(xMin+delta,average,deviation));
        steps.append(delta);

        //xMax = counter > xMax ? xMax + 1 : xMax;
        yMax = values.last() > yMax ? values.last() : yMax;

        delta += delta_plus;
        i++;
    }


    //    for (auto i = v.begin(); i != v.end(); ++i)
    //    {
    //        values.append(gaus((double)i->count,average,deviation));
    //        steps.append(delta);

    //        //xMax = counter > xMax ? xMax + 1 : xMax;
    //        yMax = values.last() > yMax ? values.last() : yMax;

    //        delta += delta_plus;
    //    }


    auto graf = ui->graphWidget->addGraph();

    QPen pen(Qt::blue);
    pen.setWidth(3);

    graf->setPen(pen);
    graf->setData(steps, values);

    double dX = max(steps) - min(steps);
    xMin -= DELTA * dX;
    xMax += DELTA * dX;

    double dY = max(values) - min(values);
    yMin -= DELTA * dY;
    yMax += DELTA * dY;

    ui->graphWidget->xAxis->setRange(xMin, xMax);
    ui->graphWidget->yAxis->setRange(yMin, yMax);

    ui->graphWidget->xAxis->setLabel("Количество повторений в диагнозе");
    ui->graphWidget->yAxis->setLabel("Значение функции нормального распределения");
    ui->graphWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->graphWidget->replot();
}

double Graph::gaus(double x, double av, double dev)
{
    return 1/(sqrt(2*M_PI*dev*dev))*exp(-(x-av)*(x-av)/(2*dev*dev));
}
