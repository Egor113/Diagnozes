#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>

#include "source.h"

class Builder : public QObject
{
    Q_OBJECT
public:
    explicit Builder(QObject *parent = 0);
    virtual ~Builder() {}
//Сделать виртуальный метод, который будетна вход будет принимать qcustomplot*

    inline void setTable(QTableWidget *t) { m_table = t; }
    inline void setFileName(const QString &file) { m_fileName = file; }

public slots:
    void start() { work(); }

signals:
    void finished();

protected:
    QTableWidget * m_table;
    QString m_fileName;

    virtual void work() = 0;

};

#endif // BUILDER_H
