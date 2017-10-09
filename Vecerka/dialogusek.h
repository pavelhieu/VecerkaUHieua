#ifndef DIALOGUSEK_H
#define DIALOGUSEK_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogUsek;
}

class DialogUsek : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUsek(QWidget *parent = 0);
    QString NazevUsek();
    QString ZboziUsek();
    int IDVecerkyUsek();
    ~DialogUsek();


private:
    Ui::DialogUsek *ui;
};

#endif // DIALOGUSEK_H
