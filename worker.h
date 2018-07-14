#ifndef WORKER_H
#define WORKER_H

#include <QThread>

#include "builder.h"

class Worker : public QThread
{

    Q_OBJECT

public:
    Worker(Builder * b, QObject * parent = 0);

    void setTable(QTableWidget * w);

private:
    Builder * m_builder;

};

#endif // WORKER_H
