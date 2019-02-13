#include "dia.h"
#include "ui_dia.h"

#include <QDebug>

Dia::Dia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
}

Dia::~Dia()
{
    delete ui;
}

void Dia::setPlotParams(QString str, QVector<CurrWordDia> vect)
{
    word = str;
    v = vect;
}

void Dia::setGraphWord(QString word)
{
    this->word = word;
}

void Dia::setGraphData(const QVector<int> &vec, const QStringList &ds)
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


void Dia::on_pushButton_clicked()
{
     QCustomPlot * customPlot = ui->widget;

     int vmax = v[0].count;

     fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

     // Установки цвета:
     QPen pen;
     pen.setWidthF(1.5);//Толщина контура столбца
     fossil->setName(word); // Легенда
     pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
     fossil->setPen(pen);
     // Цвет самого столбца, четвертый параметр - прозрачность
     fossil->setBrush(QColor(50, 50, 250, 70));

     // Установки значений оси X:

     sort();

     QVector<double> ticks;
     QVector<QString> labels;
     for(int i = 0; i < v.size(); ++i) {
         ticks << i+1;
         if (vmax < v[i].count) vmax = v[i].count;
         //qDebug() << "vmax = " << vmax;
         customPlot->xAxis->tickVectorLabels() << v[i].diagID;
         labels.append(v[i].diagID);

     }
     // !!!
     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
     textTicker->addTicks(ticks, labels);
     customPlot->xAxis->setTicker(textTicker);
     customPlot->xAxis->setTickLabelRotation(60); // Повернем на 60 градусов

     customPlot->xAxis->setTickLength(0, 4);
     customPlot->xAxis->grid()->setVisible(true);
     customPlot->xAxis->setRange(0, v.size()+1);

     // Установки значений оси Y:
     customPlot->yAxis->setRange(0, vmax+1);
     customPlot->yAxis->setPadding(5);
     customPlot->yAxis->setLabel(QString::fromUtf8("Частота повторения"));
     customPlot->yAxis->grid()->setSubGridVisible(true);
     QPen gridPen;
     gridPen.setStyle(Qt::SolidLine);
     gridPen.setColor(QColor(0, 0, 0, 25));
     customPlot->yAxis->grid()->setPen(gridPen);
     gridPen.setStyle(Qt::DotLine);
     customPlot->yAxis->grid()->setSubGridPen(gridPen);


     // Данные:
     QVector<double> fossilData;
     for(int i = 0; i < v.size(); ++i)
         fossilData.append(static_cast<double>( (v[i].count)) );

     fossil->setData(ticks, fossilData);

     // Легенда:
     customPlot->legend->setVisible(true);
     customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     customPlot->legend->setBrush(QColor(255, 255, 255, 200));
     QPen legendPen;
     legendPen.setColor(QColor(130, 130, 130, 200));
     customPlot->legend->setBorderPen(legendPen);
     QFont legendFont = font();
     legendFont.setPointSize(10);
     customPlot->legend->setFont(legendFont);
     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     customPlot->replot();

     // Сброс всех установок графика:
     customPlot->removePlottable(fossil);

}

void Dia::sort()
{
    qSort(v.begin(), v.end(), sortCondition);
}

bool Dia::sortCondition(CurrWordDia c1, CurrWordDia c2)
{
    return c1.count > c2.count;
}
