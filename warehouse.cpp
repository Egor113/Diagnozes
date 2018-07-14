#include "warehouse.h"

#include <QFile>
#include <QDebug>

#include "wordranger.h"
#include "worddsranger.h"

Worker *WareHouse::analise(const WareHouse::Mode &mode, const QString &filename)
{
    Worker * out = nullptr;

    switch (mode) {
        case Word: out = analiseByWord(filename); break;
        case WordDs: out = analiseByWordDs(filename); break;
    default:
        break;
    }

    return out;
}

Worker *WareHouse::analiseByWord(const QString &fileName)
{
    QFile f(fileName);

    if (!f.exists())
        return nullptr;

    Worker * worker = nullptr;
    auto ranger = new Wordranger();

    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&f);
        while (!stream.atEnd())
        {
            QString s = stream.readLine();
            QStringList list = s.split(";");
            QString _s = list.at(13);
            QStringList _list = _s.split(",", QString::SkipEmptyParts);

            for (auto i : _list)
            {
                for (auto j : i.split(QRegExp("\\W+"), QString::SkipEmptyParts))
                {
                    if (!j.length())
                        continue;

                    ranger->addPair(j);
                }
            }
        }

        f.close();
    }

    worker = new Worker(ranger);

    return worker;
}

Worker *WareHouse::analiseByWordDs(const QString &fileName)
{
    QFile f(fileName);

    if (!f.exists())
        return nullptr;

    Worker * worker = nullptr;
    auto ranger = new WordDsRanger();

    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&f);
        while (!stream.atEnd())
        {
            //11-ds
            QString full = stream.readLine();
            QStringList fullList = full.split(";");
            QString dia = fullList.at(10);

            QRegExp rx("\\w\\d+.\\d+");
            QStringList list;
            int pos = 0;

            while ((pos = rx.indexIn(dia, pos)) != -1) {
                list << rx.cap();
                pos += rx.matchedLength();
            }

            if (list.count() == 1)
            {
                dia = list.first();

                QString _s = fullList.at(13);
                QStringList _list = _s.split(",", QString::SkipEmptyParts);

                for (auto i : _list)
                {
                    for (auto j : i.split(QRegExp("\\W+"), QString::SkipEmptyParts))
                    {
                        if (!j.length())
                            continue;

//                        ranger->addRecord(dia, j);
                        ranger->addPair(dia, j);
                    }
                }
            }

//            qDebug() << list;
        }

        f.close();
    }

    worker = new Worker(ranger);

    return worker;
}
