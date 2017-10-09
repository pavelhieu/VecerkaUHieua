#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QInputDialog>
#include <QItemSelectionModel>
#include <QSqlError>

#include "dialog.h"
#include "dialogzame.h"
#include "dialogusek.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Vecerka/data.sqlite");
    db.open();

    model_vecerka = new QSqlTableModel(this);
    model_vecerka->setTable("vecerka");
    model_vecerka->select();

    ui->tableViewVecerka->setModel(model_vecerka);
    ui->tableViewVecerka->setSelectionBehavior(QAbstractItemView::SelectRows);
    model_vecerka->select();

    model_usek= new QSqlTableModel(this);
    model_zame= new QSqlTableModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        qDebug() << "Karta Vecerky";
         qDebug() << ui->tabWidget->currentIndex();
        break;
    case 1:{
        qDebug() << "Karta zamestnance";
         qDebug() << ui->tabWidget->currentIndex();
        int id_vecerka = ui->id_vecerka->text().toInt();
        model_zame = new QSqlTableModel;
        model_zame->setTable("zamestnanec");
        model_zame->setFilter("id_vecerka = "+ QString::number(id_vecerka));
        model_zame->select();
        ui->tableViewZamestnanec->setModel(model_zame);
    }break;
    case 2:{
        qDebug() << ui->tabWidget->currentIndex();
        int id_zame = ui->id_zame->text().toInt();
        model_usek = new QSqlTableModel;
        model_usek->setTable("usek");
        model_usek->setFilter("id_zame = " + QString::number(id_zame));
        model_usek->select();
        ui->tableViewUsek->setModel(model_usek);
    }break;
    }
}


void MainWindow::on_pushButtonPridatVecerka_clicked()
{
    //pridat novou vecerku
    Dialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << dialog.NazevVecerky();
        qDebug() << dialog.AdresaVecerky();
        qDebug() << dialog.getIDZame();
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO vecerka VALUES(NULL, :nazev, :adresa, :id_zam)");
        dotaz.bindValue(":nazev", dialog.NazevVecerky());
        dotaz.bindValue(":adresa", dialog.AdresaVecerky());
        dotaz.bindValue(":id_zame", dialog.getIDZame());
        dotaz.exec();
        model_vecerka->select();
    }
}

void MainWindow::on_pushButtonSmazatVecerka_clicked()
{
    //smazat vecerku
    QItemSelectionModel *selected = ui->tableViewVecerka->selectionModel();
    QString sql = QString("DELETE FROM vecerka WHERE id IN(");
    if (selected->selectedRows().count() == 0) {
        return;
    }
    for (int i = 0; i < selected->selectedRows().count(); ++i) {
        QModelIndex index = selected->selectedRows()[i];
        int id = model_vecerka->data(index).toInt();
        sql += QString::number(id);
        if (i!=selected->selectedRows().count()-1) {
            sql +=", ";  
        }
//         qDebug() << sql;
        //smazat zamestnanec pri smazani vecerky
         QString sql1 = QString("DELETE FROM zamestnanec WHERE id_vecerka IN(");
         sql1 +=QString::number(id);
         sql1 +=")";
         QSqlQuery dotaz1;
         dotaz1.prepare(sql1);
         dotaz1.exec();

         // smazat usek pri smazani vecerky
         QString sqlSmazatUsek = QString("DELETE FROM usek WHERE id_vecer IN(");
         sqlSmazatUsek += QString::number(id);
         sqlSmazatUsek += ")";
         qDebug() << sqlSmazatUsek;
         QSqlQuery dotazSmazatUsek;
         dotazSmazatUsek.prepare(sqlSmazatUsek);
         dotazSmazatUsek.exec();
         model_vecerka->select();
    }
    sql += ")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    model_vecerka->select();
}

void MainWindow::on_pushButtonUpravitVecerka_clicked()
{
    QItemSelectionModel *selected= ui->tableViewVecerka->selectionModel();
    QModelIndex index = selected->selectedRows().at(0);
    ui->id_vecerka->setNum(model_vecerka->data(index).toInt());
    ui->tabWidget->setCurrentIndex(1); //prepne na dalsi tab
//    if (ui->pushButtonUpravitZame->isChecked()) {
//        on_pushButtonUpravitZame_clicked();
//    }
}
void MainWindow::on_pushButtonPridatZame_clicked()
{

    DialogZame dialogZ;
    if (dialogZ.exec() == QDialog::Accepted) {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO zamestnanec VALUES(NULL, :id_vecerka, :jmeno, :prijmeni, :plat)");
        dotaz.bindValue(":id_vecerka", ui->id_vecerka->text().toInt());
        dotaz.bindValue(":jmeno", dialogZ.Jmeno());
        dotaz.bindValue(":prijmeni", dialogZ.Prijmeni());
        dotaz.bindValue(":plat", dialogZ.getPlat());
        dotaz.exec();
        model_zame->select();
    }
}

void MainWindow::on_pushButtonSmazatZame_clicked()
{
    QItemSelectionModel *selected = ui->tableViewZamestnanec->selectionModel();
    QString sql1 = QString("DELETE FROM zamestnanec WHERE id IN(");
    if (selected->selectedRows().count() == 0 ) {
        return;
    }

    for (int i = 0; i < selected->selectedRows().count(); ++i) {
        QModelIndex index =selected->selectedRows()[i];
        int id = model_zame->data(index).toInt();
        sql1 += QString::number(id);
        if (i!=selected->selectedRows().count()-1) {
            sql1 +=", ";
        }
        QString sqlSql = QString("DELETE FROM usek WHERE id_zame IN(");
        sqlSql +=QString::number(id);
        sqlSql += ")";
        qDebug() << QString(sqlSql);
        QSqlQuery dotaz1;
        dotaz1.prepare(sqlSql);
        dotaz1.exec();
        model_zame->select();
        }
      sql1 += ")";
    QSqlQuery dotaz;
    dotaz.prepare(sql1);
    dotaz.exec();
    model_zame->select();
}
void MainWindow::on_pushButtonUpravitZame_clicked()
{
    QItemSelectionModel *selectedd = ui->tableViewZamestnanec->selectionModel();
    QModelIndex index1 = selectedd->selectedRows().at(0);
    ui->id_zame->setNum(model_zame->data(index1).toInt());
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButtonPridatUsek_clicked()
{
    // pridat Usek
    DialogUsek dialogU;
    if (dialogU.exec()== QDialog::Accepted) {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO usek VALUES(NULL, :id_zame, :id_vecer,:nazev, :zbozi)");
        dotaz.bindValue(":id_zame", ui->id_zame->text().toInt());
        dotaz.bindValue(":id_vecer", dialogU.IDVecerkyUsek());
        dotaz.bindValue(":nazev" , dialogU.NazevUsek());
        dotaz.bindValue(":zbozi", dialogU.ZboziUsek());
        dotaz.exec();
        model_usek->select();
    }
}

void MainWindow::on_pushButtonSmazatUsek_clicked()
{
    // smazat usek
    QItemSelectionModel *selected = ui->tableViewUsek->selectionModel();
    QString sql5 = QString("DELETE FROM usek WHERE id IN(");
    if (selected->selectedRows().count() ==0) {
        return;
    }
    for (int i = 0; i < selected->selectedRows().count(); ++i) {
        QModelIndex index5 = selected->selectedRows()[i];
        int id5 = model_usek->data(index5).toInt();
        sql5 += QString::number(id5);
    }
    sql5 += ")";
    qDebug() << sql5;
    QSqlQuery dotaz5;
    dotaz5.prepare(sql5);
    dotaz5.exec();
    model_usek->select();
}

// vypsat id vecerky do tabulky useku
// vypsat jmena vecerky do tabulky zamestnance
// vypsat jmeno vecerky a zamestnance do tabulky useku
// upozerneni kdyz nic nevybral
// osetrit hacky
