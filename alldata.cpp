#include <QMessageBox>
#include <QDebug>
#include <QModelIndex>

#include <QList>
#include "alldata.h"
#include "ui_alldata.h"
#include "alldatamodel.h"
#include "mainwindow.h"
#include "sqlite.h"
#include "alldatamodel.h"

AllData::AllData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllData)
{
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);

    owner = (MainWindow*)parent;
    model = new AllDataModel();

    refreshTable();
    //testData();
    //see if the data shows up now
    ui->tableView->setModel(model);

//    qDebug()<<"the model has how many rows: "<<model->rowCount(QModelIndex());

//    qDebug()<<"right before refreshTable()";
    //refreshTable();

    //qDebug()<<"after refreshTable, the model has how many rows: "<<model->rowCount(QModelIndex());
}

AllData::~AllData()
{
    delete ui;
    delete model;
}


void AllData::testData()
{
    Mileage m1;
    m1.id=3;
    m1.miles=38;
    m1.gallons=2;
    m1.cost=5.15;
    m1.date=QDate::currentDate();

    Mileage m2;
    m2.id=3;
    m2.miles=12;
    m2.gallons=1.1;
    m2.cost=3;
    //m2.date=QDate::fromString("2018-04-04");
    QDate d = QDate::fromString("2018-02-14","yyyy-MM-dd");
    //QDate d = QDate::fromString("1MM12car2003", "d'MM'MMcaryyyy");
    m2.date = d;

    model->insertRow(0,1,QModelIndex(),m1);

    model->insertRow(1,1,QModelIndex(),m2);

    qDebug()<<m1.date;
    qDebug()<<m2.date;

}

void AllData::refreshTable()
{
    //get vehicle id
    QSettings settings;
    int vehicleId = settings.value("config/vehicle").toInt();

    QString s = "select id,miles,gallons,cost,fillup_date \
            from fuel_mileage \
            where vehicle_id = :id \
            order by fillup_date desc ";

    QSqlQuery query(QSqlDatabase::database());

    query.prepare(s);
    query.bindValue(":id",vehicleId);
    //bool ok = false;

    qDebug()<<"row count:"<<model->rowCount(QModelIndex());
    if (query.exec())
    {
        //ok = true;
        while(query.next())
        {
            Mileage m;
            m.id = query.value(0).toInt();
            m.miles = query.value(1).toDouble();
            m.gallons = query.value(2).toDouble();
            m.cost = query.value(3).toDouble();
            m.date = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");
            qDebug()<<"adding a row";
            model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),m);
            qDebug()<<"not get here";
        }
    }
    else
    {
        qDebug()<<"query did not execute";
    }
}

//void AllData::refreshTable()
//{
//    //clear the model
//    //model->clear();

//    //get vehicle id
//    QSettings settings;
//    int vehicleId = settings.value("config/vehicle").toInt();
//    QString dbaseType = settings.value("config/databasetype").toString();
//    //QList<Mileage>*m = new QList();
//    QList<Mileage>m;
//    if (dbaseType == "sqlite")
//    {
//        Sqlite *c = (Sqlite*)owner->getConnection();
//        if (c->selectFuelMileage(vehicleId,model))
//        {
//            //do something here
//            qDebug()<<"selecting the fuelmileage";
//            qDebug()<<"how many records:"<<m.size();
//        }
//        else
//        {
//            QMessageBox msg(QMessageBox::Critical,"Can't get Data","something happened with selecFuelMileage" ,QMessageBox::Ok,this);
//            msg.exec();
//        }
//    }
////    qDebug()<<"the list is crashing...";
////    //put the list into the model
////    for(int i=0;i<m.size();i++)
////    {
////        model->insertRows(0,1,QModelIndex());
////        QModelIndex index = model->index(0,0,QModelIndex());
////        model->setData(index,m.at(i).id,Qt::EditRole);

////        index = model->index(0,1,QModelIndex());
////        model->setData(index,m.at(i).miles,Qt::EditRole);

////        index = model->index(0,2,QModelIndex());
////        model->setData(index,m.at(i).gallons,Qt::EditRole);

////        index = model->index(0,3,QModelIndex());
////        model->setData(index,m.at(i).cost,Qt::EditRole);

////        index = model->index(0,4,QModelIndex());
////        model->setData(index,m.at(i).date,Qt::EditRole);

////    }
//}
