#ifndef WORDRANGER_H
#define WORDRANGER_H

#include <QPair>

#include "builder.h"

class Wordranger : public Builder
{
public:
    Wordranger();

    void addPair(const QString &str);

protected:

// Builder interface
    void work();

// Wordranger interface
    virtual void chainMake(QString &str);

private:
    QList< QPair<QString, int> > m_wordPairs;

    void sort();
};

#endif // WORDRANGER_H
