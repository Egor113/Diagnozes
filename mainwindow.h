#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "dia.h"

/*!
    \brief Касаемо Графиков

    \details
        Кнопка "показать диаграмму/график" рождает объект диаграммы
        Соединение сигналов нажатия на эти кнопки со слотом openFile()
        + сигнал нажатой кнопки на форме диаграммы соединить со слотом Buildera,
        в котором будет происходить анализ

*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void openFile();
    void showdia();

private:
    Ui::MainWindow *ui;
    QTableWidgetItem * m_item;
    Dia *dia;

};

#endif // MAINWINDOW_H
