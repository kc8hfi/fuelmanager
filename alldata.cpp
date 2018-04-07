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

    //resize the date column
    QHeaderView *hview = ui->tableView->horizontalHeader();
    hview->resizeSection(1,200);

    //hide the first column
    ui->tableView->setColumnHidden(0,true);
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
    //clean out the model first
    model->removeRows(0,model->rowCount(QModelIndex()));
    model->clearColor();
    if (!owner->getQuery()->selectFuelMileage(vehicleId,model))
    {
        qDebug()<<"couldn't get the fuel mileage data";
    }


    if(settings.value("config/databasetype").toString() == "sqlite")
    {
//        Sqlite* c = (Sqlite*)owner->getConnection();
//        //empty the model first
//        model->removeRows(0,model->rowCount(QModelIndex()));
//        //empty the colors first
//        model->clearColor();
//        if(!c->selectFuelMileage(vehicleId,model))
//        {
//            qDebug()<<"didn't get the fuel mileage data";
//        }
//        //qDebug()<<"records:"<<model->rowCount(QModelIndex());
//        //qDebug()<<"colors:"<<model->sizeColor();
    }
}
