#include <QMessageBox>
#include <QDebug>
#include <QModelIndex>
#include "alldata.h"
#include "ui_alldata.h"
#include "alldatamodel.h"
#include "mainwindow.h"
#include "sqlite.h"

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

    refreshTable();

    qDebug()<<"after refreshTable, the model has how many rows: "<<model->rowCount(QModelIndex());
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
    if (dbaseType == "sqlite")
    {
        Sqlite *c = (Sqlite*)owner->getConnection();
        if (c->selectFuelMileage(vehicleId,model))
        {
            //do something here
            qDebug()<<"selecting the fuelmileage";

        }
        else
        {
            QMessageBox msg(QMessageBox::Critical,"Can't get Data","something happened with selecFuelMileage" ,QMessageBox::Ok,this);
            msg.exec();
        }
    }
}
