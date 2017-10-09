#include "dialogusek.h"
#include "ui_dialogusek.h"
#include "mainwindow.h"

DialogUsek::DialogUsek(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUsek)
{
    ui->setupUi(this);
}

QString DialogUsek::NazevUsek()
{
    return ui->lineEditNazevUsek->text();
}

QString DialogUsek::ZboziUsek()
{
    return ui->lineEditZboziUsek->text();
}

int DialogUsek::IDVecerkyUsek()
{
    return ui->spinBoxIdVecerkyUsek->value();
}

DialogUsek::~DialogUsek()
{
    delete ui;
}


