#ifndef DIALOGZAME_H
#define DIALOGZAME_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogZame;
}

class DialogZame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogZame(QWidget *parent = 0);
    QString Jmeno();
    QString Prijmeni();
    int getPlat();
    ~DialogZame();

private:
    Ui::DialogZame *ui;
};

#endif // DIALOGZAME_H
