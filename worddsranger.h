#ifndef WORDDSRANGER_H
#define WORDDSRANGER_H

#include <QPair>

#include "builder.h"

struct Data {
    QString ds;
    QList < QPair<QString, int> > list;
    double code() const {
        QRegExp rx("\\d+.\\d+");
        QString value;
        int pos = 0;

        while ((pos = rx.indexIn(ds, pos)) != -1) {
            value = rx.cap();
            pos += rx.matchedLength();
        }

        return value.toDouble();
    }
    bool operator >(const Data &other)
    {
        return this->code() > other.code();
    }
};

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
