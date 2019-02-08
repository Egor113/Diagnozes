#ifndef SOURCE_H
#define SOURCE_H

#include <QString>

struct CurrWordDia// Структура для хранения диагноза
               // и частоты
{
    QString diagID;
    int count;
};

#define DELTA 0.05

template <typename T>
T max(const QVector<T> &vec)
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
T min(const QVector<T> &vec)
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

#endif // SOURCE_H
