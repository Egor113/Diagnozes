#include "worddsranger.h"

#include <QDebug>

WordDsRanger::WordDsRanger() : m_dataLength(0)
{

}

WordDsRanger::~WordDsRanger()
{
    // !!!!!!!!!!!!!!!
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

                Source::removeUselessBrackets(_s);

                chainMake(dia, _s);
            }
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
    if (this->type == "worddsranger"){
        header << "Диагноз" << "Слова" << "Количество повторов";
    }
    else {
        header << "Диагноз" << "Симптомы" << "Количество повторов";
    }
    m_table->setHorizontalHeaderLabels(header);

    int count = 0;

    sort();

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

void WordDsRanger::chainMake(QString dia, QString &str)
{
    QStringList _list = str.split(",", QString::SkipEmptyParts);

    for (auto i : _list)
    {
        for (auto j : i.split(QRegExp("\\W+"), QString::SkipEmptyParts))
        {
            if (j.length() < 3)
                continue;

            addPair(dia, j);
        }
    }
}

void WordDsRanger::sort()
{
    qSort(m_data.begin(), m_data.end(), [](Data*a, Data*b){
        return *b > *a;
    });

    for (auto i : m_data)
    {
        qSort(i->list.begin(), i->list.end(), []
              (const QPair<QString, int> &a, const QPair<QString, int> &b
              ){
            return a.second > b.second;
        });
    }
}
