#ifndef WORDDSRANGER_H
#define WORDDSRANGER_H

#include <QPair>

#include "builder.h"
#include "source.h"



class WordDsRanger : public Builder
{
public:
    WordDsRanger();
    ~WordDsRanger();

    void addRecord(const QString &ds, const QString &word); // К удалению
    void addPair(const QString &ds, const QString &word);

protected:

// Builder interface
    void work();

private:
    QList< QPair<QString, QList< QPair<QString, int> > > > m_wordDsMap; // К Удалению
    QList<Data*> m_data;

    void sort();

    int m_dataLength;
};

#endif // WORDDSRANGER_H
