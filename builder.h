#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QTableWidget>

class Builder : public QObject
{
    Q_OBJECT
public:
    explicit Builder(QObject *parent = 0);

    inline void setTable(QTableWidget *t) { m_table = t; }

public slots:
    void start() { work(); }

protected:
    QTableWidget * m_table;

    virtual void work() = 0;

};

#endif // BUILDER_H
