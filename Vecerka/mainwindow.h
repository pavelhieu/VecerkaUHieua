#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:

private slots:
    void on_pushButtonPridatVecerka_clicked();
    void on_pushButtonSmazatVecerka_clicked();

    void on_pushButtonUpravitVecerka_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonPridatZame_clicked();

    void on_pushButtonSmazatZame_clicked();

    void on_pushButtonUpravitZame_clicked();

    void on_pushButtonPridatUsek_clicked();

    void on_pushButtonSmazatUsek_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model_vecerka;
    QSqlTableModel *model_zame;
    QSqlTableModel *model_usek;

};

#endif // MAINWINDOW_H
