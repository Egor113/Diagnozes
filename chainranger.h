#ifndef CHAINRANGER_H
#define CHAINRANGER_H

#include <QPair>

#include "wordranger.h"

class Chainranger : public Wordranger
{
public:
    Chainranger();

protected:

// Builder interface
    void work();

// Wordranger interface
    void chainMake(QString &str);

private:
    QList< QPair<QString, int> > m_wordPairs;

};

#endif // CHAINRANGER_H
