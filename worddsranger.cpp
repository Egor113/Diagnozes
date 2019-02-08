#include "worddsranger.h"

#include <QDebug>

WordDsRanger::WordDsRanger() : m_dataLength(0)
{

}

WordDsRanger::~WordDsRanger()
{
    // !!!!!!!!!!!!!!!
}

void WordDsRanger::addRecord(const QString &ds, const QString &word)
{
    QList< QPair<QString, int> > * target = nullptr;

    // these all wrong !

}

void WordDsRanger::addPair(const QString &ds, const QString &word)
{
    for (auto i: m_data)
    {
        if (i->ds.compare(ds, Qt::CaseInsensitive) == 0)
        {
            bool found = false;

            for (auto j = i->list.begin(); j != i->list.end(); ++j)
            {
                if ((*j).first.compare(word, Qt::CaseInsensitive) == 0)
                {
                    (*j).second++;
                    return;
                }
            }

            if (!found)
            {
                i->list.append(QPair<QString, int>(word, 1));
                m_dataLength++;
                return;
            }
        }
    }

    auto d = new Data();
    d->ds = ds;
    d->list.append(QPair<QString, int>(word, 1));
    m_data.append(d);
}

void WordDsRanger::work()
{
    QFile f(this->m_fileName);

    if (!f.exists())
        return;

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

                       addPair(dia, j);
                    }
                }
            }

//            qDebug() << list;
        }

        f.close();
    }

//Прорисовка таблицы

    if (!this->m_table)
        return;

    m_table->clear();
    m_table->setColumnCount(3);
    m_table->setRowCount(m_dataLength);
    QStringList header;
    header << "Диагноз" << "Слова" << "Количество повторов";
    m_table->setHorizontalHeaderLabels(header);

    int count = 0;


qDebug() << count;

for (auto i : m_data)
{

    for (auto j : i->list)
    {
        auto f = new QTableWidgetItem(i->ds);
        auto m = new QTableWidgetItem(j.first);
        auto s = new QTableWidgetItem(QString::number(j.second));

        m_table->setItem(count, 0, f);
        m_table->setItem(count, 1, m);
        m_table->setItem(count, 2, s);
        count++;
    }

}
}

void WordDsRanger::sort()
{
    qSort(m_wordDsMap.begin(), m_wordDsMap.end(), [](QPair<QString, QList< QPair<QString, int> > > &a,
          QPair<QString, QList< QPair<QString, int> > > &b) {

        QRegExp rx("\\d+.\\d+");
        QStringList listA, listB;
        int pos = 0;

        while ((pos = rx.indexIn(a.first, pos)) != -1) {
            listA << rx.cap();
            pos += rx.matchedLength();
        }

        pos = 0;

        while ((pos = rx.indexIn(b.first, pos)) != -1) {
            listB << rx.cap();
            pos += rx.matchedLength();
        }
        qDebug() << listA << listB;

        return listA.first().toDouble() > listB.first().toDouble();
    });
}
