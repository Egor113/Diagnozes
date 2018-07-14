#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QPair>
#include <QTextStream>

#include "worker.h"

class WareHouse
{
public:

    enum Mode {
        Word,
        WordDs,
        Exp,
        ExpDs
    };

    static Worker * analise(const Mode &mode, const QString &filename);

protected:
    static Worker * analiseByWord(const QString &fileName);
    static Worker * analiseByWordDs(const QString &fileName);

};

#endif // WAREHOUSE_H
