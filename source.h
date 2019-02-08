#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QStack>

#define DELTA 0.05


/*!
  \brief Структура для хранения диагноза и частоты
*/
struct CurrWordDia
{
    QString diagID;
    int count;
};

struct Data
{
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

template <typename T>
static T max(const QVector<T> &vec)
{
    if (!vec.count())
        return (T)0;

    T max = vec[0];

    auto i = vec.begin();
    for (++i; i != vec.end(); ++i)
    {
        max = (*i) > max ? (*i) : max;
    }

    return max;
}

template <typename T>
static T min(const QVector<T> &vec)
{
    if (!vec.count())
        return (T)0;

    T min = vec[0];

    auto i = vec.begin();
    for (++i; i != vec.end(); ++i)
    {
        min = (*i) < min ? (*i) : min;
    }

    return min;
}

class Source {
public:

    static void removeUselessBrackets(QString &str)
    {
        QStack<int> opened, closed;
        int summ;
        bool isCorrect = false;

        int i;

        while (!isCorrect)
        {
            isCorrect = true;
            i = 0;
            summ = 0;

            while (i < str.length())
            {
                switch (str[i].toLatin1()) {
                case '(':
                    opened.push(i);
                    summ++;
                    break;

                case ')':
                    closed.push(i);
                    summ--;
                    if (opened.count())
                    {
                        opened.pop();
                        closed.pop();
                    }
                    else
                    {
                        isCorrect = false;
                        closed.pop();
                        str.remove(i, 1);
                        continue;
                    }
                    break;

                default:
                    break;
                }

                i++;
            }

            if (!summ)
                break;

            if (opened.count())
            {
                for (int k(0); k<opened.count(); k++)
                {
                    str.remove(opened.at(k) - k, 1);
                }
                opened.clear();
            }

            i = str.length() - 1;

            while (i >= 0)
            {
                switch (str[i].toLatin1()) {
                case ')':
                    closed.push(i);
                    break;

                case '(':
                    opened.push(i);
                    if (closed.count())
                    {
                        opened.pop();
                        closed.pop();
                    }
                    else
                    {
                        isCorrect = false;
                        opened.pop();
                        str.remove(i, 1);
                        continue;
                    }
                    break;

                default:
                    break;
                }
                i--;
            }

            if (closed.count())
            {
                for (int k(closed.count() - 1); k<=0; k--)
                {
                    str.remove(closed.at(k) - k, 1);
                }
                closed.clear();
            }
        }
    }

};





#endif // SOURCE_H
