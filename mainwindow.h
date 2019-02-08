#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include "dia.h"
#include "builder.h"

/*!
    \details
        + Сортировка
        + Регулярка для отсеивания выражений
        + Что делать с лейблами на графиках (?)
        + Убрать предлоги/союзы

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

signals:
    void wordReady(QString);
    void dataReady(const QVector<int> &vec, const QStringList &ds);

protected slots:
    void openFile();
    void showdia();
    void onCellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QTableWidgetItem * m_item;
//    Dia *dia;

};

#endif // MAINWINDOW_H
