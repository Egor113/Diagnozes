#ifndef CHAINDSRANGER_H
#define CHAINDSRANGER_H

#include <QPair>
#include <QDebug>

#include "worddsranger.h"

class Chaindsranger:  public WordDsRanger
{
public:
    Chaindsranger();

protected:

// Builder interface
    void work();

// WordDsRanger interface
    void chainMake(QString dia, QString &str);

};

#endif // CHAINDSRANGER_H
