#include "graphicsform.h"

#include <QSplitter>    // Для разделения формы

GraphicsForm::GraphicsForm(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * hLay = new QHBoxLayout(this);                 // main layout
    QSplitter * split = new QSplitter(Qt::Horizontal, this);    // Splitter object

    hLay->addWidget(split);

    m_dia = new Dia(this);
    m_graph = new Graph(this);

    split->addWidget(m_dia);
    split->addWidget(m_graph);
}

void GraphicsForm::setGraphWord(QString word)
{
    m_dia->setGraphWord(word);
    m_graph->setGraphWord(word);
}

void GraphicsForm::setGraphData(const QVector<int> &vec, const QStringList &ds)
{
    m_dia->setGraphData(vec, ds);
    m_graph->setGraphData(vec, ds);
}
