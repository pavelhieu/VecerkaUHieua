#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

QString Dialog::NazevVecerky()
{
   return ui->lineEditNazevVecerky->text();
}

QString Dialog::AdresaVecerky()
{
  return  ui->lineEditAdresaVecerky->text();
}

int Dialog::getIDZame()
{
    return ui->spinBoxIDZame->value();
}

Dialog::~Dialog()
{
    delete ui;
}

//void Dialog::accept()
//{

//    if ( ui->lineEditNazevVecerky->text().length() == 0) {
//        QMessageBox::warning(this,"Chyba","Nevyplnené okenko");
//        ui->lineEditNazevVecerky->setFocus();
//        return;
//    }
//    Dialog::accept();
//}
