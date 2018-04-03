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

    qDebug()<<"the model has how many rows: "<<model->rowCount(QModelIndex());
    ui->tableView->setModel(model);
    //qDebug()<<"right before refreshTable()";
    refreshTable();

    //qDebug()<<"after refreshTable, the model has how many rows: "<<model->rowCount(QModelIndex());
}

AllData::~AllData()
{
    delete ui;
    delete model;
}

void AllData::refreshTable()
{
    //clear the model
    //model->clear();

    //get vehicle id
    QSettings settings;
    int vehicleId = settings.value("config/vehicle").toInt();
    QString dbaseType = settings.value("config/databasetype").toString();
    //QList<Mileage>*m = new QList();
    QList<Mileage>m;
    if (dbaseType == "sqlite")
    {
        Sqlite *c = (Sqlite*)owner->getConnection();
        if (c->selectFuelMileage(vehicleId,model))
        {
            //do something here
            qDebug()<<"selecting the fuelmileage";
            qDebug()<<"how many records:"<<m.size();
        }
        else
        {
            QMessageBox msg(QMessageBox::Critical,"Can't get Data","something happened with selecFuelMileage" ,QMessageBox::Ok,this);
            msg.exec();
        }
    }
//    qDebug()<<"the list is crashing...";
//    //put the list into the model
//    for(int i=0;i<m.size();i++)
//    {
//        model->insertRows(0,1,QModelIndex());
//        QModelIndex index = model->index(0,0,QModelIndex());
//        model->setData(index,m.at(i).id,Qt::EditRole);

//        index = model->index(0,1,QModelIndex());
//        model->setData(index,m.at(i).miles,Qt::EditRole);

//        index = model->index(0,2,QModelIndex());
//        model->setData(index,m.at(i).gallons,Qt::EditRole);

//        index = model->index(0,3,QModelIndex());
//        model->setData(index,m.at(i).cost,Qt::EditRole);

//        index = model->index(0,4,QModelIndex());
//        model->setData(index,m.at(i).date,Qt::EditRole);

//    }
}
