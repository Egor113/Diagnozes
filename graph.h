#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "source.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

public slots:
    void setGraphWord(QString word);
    void setGraphData(const QVector<int> &vec, const QStringList &ds);  // Вектор значений и лист наименований диагнозов

protected slots:
    void printGraph();

private:
    Ui::Graph *ui;

    QString word; //Строка для храения слова (выражения)
    QVector<CurrWordDia> v; //Вектор для хранения диагноза и частоты

    double gaus(double x, double av, double dev);
};

#endif // GRAPH_H
