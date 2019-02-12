#ifndef DIA_H
#define DIA_H

#include <QWidget>

#include "qcustomplot.h"
#include "source.h"

// ГИСТОГРАММА

namespace Ui {
class Dia;
}

class Dia : public QWidget
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = 0);
    ~Dia();
    void setPlotParams(QString str, QVector<CurrWordDia> vect);// Процедура инициализации

public slots:
    void setGraphWord(QString word);
    void setGraphData(const QVector<int> &vec, const QStringList &ds);  // Вектор значений и лист наименований диагнозов

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dia *ui;
    QCPBars *fossil;

    QString word; //Строка для храения слова (выражения)
    QVector<CurrWordDia> v; //Вектор для хранения диагноза и частоты
    void sort();
    bool static sortCondition(CurrWordDia c1, CurrWordDia c2);
};

#endif // DIA_H
