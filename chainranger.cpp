#include "chainranger.h"

#include <QDebug>

Chainranger::Chainranger()
{

}

void Chainranger::work()
{
    Wordranger::work();
}

void Chainranger::chainMake(QString &str)
{
    QRegExp rx("\\(((\\s+|\\w+|([а-яА-Я,-\\/]+)+){1,})\\)");
    int pos = 0;

    while((pos = rx.indexIn(str,pos)) != -1)
    {
        QString word;
        word = rx.cap();
        word.remove(QRegExp("\\(|\\)"));
        chainMake(word);
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

        addPair(s.remove(QRegExp("^\\s+|\\.|\"")));
    }
}

