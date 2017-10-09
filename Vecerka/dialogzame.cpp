#include "dialogzame.h"
#include "ui_dialogzame.h"
#include <QSqlDatabase>
#include <QDialog>

DialogZame::DialogZame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogZame)
{
    ui->setupUi(this);
}

QString DialogZame::Jmeno()
{
    return ui->lineEditJmenoZame->text();
}

QString DialogZame::Prijmeni()
{
    return ui->lineEditPrijmeniZame->text();
}

int DialogZame::getPlat()
{
    return ui->spinBoxPlat->value();
}

DialogZame::~DialogZame()
{
    delete ui;
}
