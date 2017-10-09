#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    QString NazevVecerky();
    QString AdresaVecerky();
    int getIDZame();
    ~Dialog();
private slots:
//     void accept();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
