#include "wordranger.h"

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
            founded = true;
            break;
        }
    }

    if (!founded)
    {
        m_wordPairs.append(QPair<QString, int>(str, 1));
    }
}

void Wordranger::work()
{
    if (!this->m_table)
        return;

    m_table->clear();
    m_table->setColumnCount(2);
    m_table->setRowCount(m_wordPairs.count());

    int count = 0;

    sort();

    for (auto i : m_wordPairs)
    {
        auto f = new QTableWidgetItem(i.first);
        auto s = new QTableWidgetItem(QString::number(i.second));

        m_table->setItem(count, 0, f);
        m_table->setItem(count, 1, s);

        count++;
    }
}

void Wordranger::sort()
{
    qSort(m_wordPairs.begin(), m_wordPairs.end(), [](QPair<QString, int> &a, QPair<QString, int> &b){
        return a.second > b.second;
    });
}
