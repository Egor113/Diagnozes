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

#endif // SOURCE_H
