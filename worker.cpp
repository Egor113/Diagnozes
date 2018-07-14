#include "worker.h"

Worker::Worker(Builder *b, QObject *parent) : QThread(parent), m_builder(b)
{
    m_builder->setParent(this);

    QObject::connect(this, &Worker::started, m_builder, &Builder::start);
}

void Worker::setTable(QTableWidget *w)
{
    if (m_builder)
        m_builder->setTable(w);
}
