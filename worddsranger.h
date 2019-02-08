#ifndef WORDDSRANGER_H
#define WORDDSRANGER_H

#include <QPair>

#include "builder.h"

class WordDsRanger : public Builder
{
public:
    WordDsRanger();
    ~WordDsRanger();

    void addPair(const QString &ds, const QString &word);

protected:

// Builder interface
    void work();

    virtual void chainMake(QString dia, QString &str);

    int m_dataLength;

private:
    QList<Data*> m_data;

    void sort();
    void sordDs();
    bool static dsIsBigger(QString s1, QString s2);

};

#endif // WORDDSRANGER_H
