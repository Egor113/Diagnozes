#ifndef CHAINRANGER_H
#define CHAINRANGER_H

#include <QPair>
#include "builder.h"

class Chainranger : public Builder
{
public:
    Chainranger();

    void addPair(const QString &str);

protected:

    // Builder interface
        void work();
private:
    QList< QPair<QString, int> > m_wordPairs;

    void sort();
};

#endif // CHAINRANGER_H
