#ifndef GRAPHICSFORM_H
#define GRAPHICSFORM_H

#include <QWidget>

#include "dia.h"        // Gistogramm
#include "graph.h"      // Normal graphic

class GraphicsForm : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsForm(QWidget *parent = nullptr);

public slots:
    void setGraphWord(QString word);
    void setGraphData(const QVector<int> &vec, const QStringList &ds);  // Вектор значений и лист наименований диагнозов

private:
    Dia * m_dia;
    Graph * m_graph;

};

#endif // GRAPHICSFORM_H
