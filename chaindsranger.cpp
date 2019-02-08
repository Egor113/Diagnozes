#include "chaindsranger.h"

Chaindsranger::Chaindsranger()
{
    this->m_dataLength = 0;
}

void Chaindsranger::work()
{
    WordDsRanger::work();
}

void Chaindsranger::chainMake(QString dia, QString &str)
{
    QRegExp rx("\\(((\\s+|\\w+|([а-яА-Я,-\\/]+)+){1,})\\)");
    int pos = 0;

    while((pos = rx.indexIn(str,pos)) != -1)
    {
        QString word;
        word = rx.cap();
        word.remove(QRegExp("\\(|\\)"));
        chainMake(dia, word);
        str.remove(pos, rx.matchedLength());
        str.insert(pos, ",");
        if (word.count())
            pos = 0;
        else
            pos += rx.matchedLength();
    }

    str.remove(QRegExp("\\(\\)"));

    for (auto s : str.split(QRegExp(",|-"), QString::SkipEmptyParts))
    {
        if (s.length() < 3)
            continue;

        addPair(dia, s.remove(QRegExp("^\\s+|\\.|\"")));
    }
}

