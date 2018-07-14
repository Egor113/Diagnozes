#ifndef DIA_H
#define DIA_H

#include <QWidget>

namespace Ui {
class Dia;
}

class Dia : public QWidget
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = 0);
    ~Dia();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dia *ui;
};

#endif // DIA_H
