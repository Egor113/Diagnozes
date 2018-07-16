#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class Dia;
}

struct CurrWordDia// Структура для хранения диагноза
               // и частоты
{
    QString diagID;
    int count;
};

class Dia : public QWidget
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = 0);
    ~Dia();
    QString word; //Строка для храения слова (выражения)
    QVector<CurrWordDia> v; //Вектор для хранения диагноза и частоты
    void setPlotParams(QString str, QVector<CurrWordDia> vect);// Процедура инициализации

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dia *ui;
    QCPBars *fossil;
};

#endif // DIA_H
