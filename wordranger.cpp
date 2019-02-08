#include "wordranger.h"

#include <QDebug>

Wordranger::Wordranger()
{

}

void Wordranger::addPair(const QString &str)
{
    bool founded = false;

    for (auto i = m_wordPairs.begin(); i != m_wordPairs.end(); ++i)
    {
        if (!(*i).first.compare(str, Qt::CaseInsensitive))
        {
            (*i).second++;
            return;
        }
    }

    if (!founded)
    {
        m_wordPairs.append(QPair<QString, int>(str, 1));
    }
}

void Wordranger::work()
{
    QFile f(this->m_fileName);

    if (!f.exists())
        return;

    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&f);

        bool firstLine = false;
        while (!stream.atEnd() && !firstLine)
        {
            stream.readLine();
            firstLine = true;
        }

        while (!stream.atEnd())
        {
            QString s = stream.readLine();
            QStringList list = s.split(";");
            QString _s = list.at(13);

            Source::removeUselessBrackets(_s);

            chainMake(_s);
        }

        f.close();
    }

//Прорисовка таблицы

    if (!this->m_table)
        return;

    m_table->clear();
    m_table->setColumnCount(2);
    m_table->setRowCount(m_wordPairs.count());
    QStringList header;
    header << "Слова" << "Количество повторов";
    m_table->setHorizontalHeaderLabels(header);

    int count = 0;
    qDebug() << m_wordPairs.count();
    sort();

    for (auto i : m_wordPairs)
    {
        auto f = new QTableWidgetItem(i.first);
        auto s = new QTableWidgetItem(QString::number(i.second));

        m_table->setItem(count, 0, f);
        m_table->setItem(count, 1, s);

        count++;
        qDebug() << count;
    }
    qDebug() << "Some";
    emit finished();
}

void Wordranger::chainMake(QString &str)
{
    QStringList _list = str.split(",", QString::SkipEmptyParts);

    for (auto i : _list)
    {
        for (auto j : i.split(QRegExp("\\W+"), QString::SkipEmptyParts))
        {
            if (j.length() < 3)
                continue;

            addPair(j);
        }
    }
}

void Wordranger::sort()
{
    qSort(m_wordPairs.begin(), m_wordPairs.end(), [](QPair<QString, int> &a, QPair<QString, int> &b){
        return a.second > b.second;
    });
}
