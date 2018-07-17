#include "chainranger.h"

#include <QDebug>

Chainranger::Chainranger()
{

}

void Chainranger::addPair(const QString &str)
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

void Chainranger::work()
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
            QStringList _list = _s.split(",", QString::SkipEmptyParts);

            for (auto i : _list)
            {
                for (auto j : i.split(QRegExp("\\((\\s+|\\w+|([а-я]|[А-Я])+){1,}\\)"), QString::SkipEmptyParts))
                {
                    if (!j.length())
                        continue;

                    addPair(j);
                }
            }
        }

        f.close();
    }

//Прорисовка таблицы

    if (!this->m_table)
        return;

    m_table->clear();
    m_table->setColumnCount(2);
    m_table->setRowCount(m_wordPairs.count());

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

void Chainranger::sort()
{
    qSort(m_wordPairs.begin(), m_wordPairs.end(), [](QPair<QString, int> &a, QPair<QString, int> &b){
        return a.second > b.second;
    });
}
