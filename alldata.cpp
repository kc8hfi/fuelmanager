#include <QMessageBox>
#include <QDebug>
#include <QModelIndex>

#include <QList>
#include <QSettings>
#include "alldata.h"
#include "ui_alldata.h"
#include "alldatamodel.h"
#include "datedelegate.h"
#include "query.h"

AllData::AllData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllData)
{
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);

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

    //set a delegate for the date column
    ui->tableView->setItemDelegateForColumn(1,new DateDelegate(parent));

    //clear out the list of changed items
    changedItems.clear();

    //connect the datachanged from the model
    connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(changedItem(const QModelIndex &,const QModelIndex &)));

    connect(ui->saveButton,SIGNAL(clicked(bool)),this,SLOT(saveData()));
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
    Query queries;
    queries.selectFuelMileage(vehicleId,model);

    //set the information field
    ui->informationLabel->setText(QString::number(model->rowCount(QModelIndex())) + " records.");

}

void AllData::changedItem(const QModelIndex& topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    auto m = model->getItem(topLeft.row());
    //qDebug()<<"id:"<<m.id<<" miles:"<<m.miles<<" gallons:"<<m.gallons;

    //find out of m.id is already in there
    //if it is,  modify it
    //otherwise, append it
    bool found = false;
    int index = 0;
    for(int i=0;i<changedItems.size();i++)
    {
        Mileage t = changedItems.at(i);
        if (t.id == m.id)
        {
            index = i;
            found = true;
            break;
        }
    }
    if (found)
        changedItems.replace(index,m);
    else
        changedItems.append(m);

    ui->saveButton->setEnabled(true);
}

void AllData::saveData()
{
//    qDebug()<<"save these items";
//    for(int i=0;i<changedItems.size();i++)
//    {
//        auto m = changedItems.at(i);
//        qDebug()<<"id:"<<m.id<<" miles:"<<m.miles<<" gallons:"<<m.gallons;
//    }
    Query q;
    if (q.updateFuelMileage(changedItems))
    {
        //save was ok, clear the list
        changedItems.clear();
        ui->saveButton->setEnabled(false);
        refreshTable();
    }
}
