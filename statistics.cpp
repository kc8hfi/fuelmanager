#include "statistics.h"
#include "ui_statistics.h"
#include <QVBoxLayout>
#include <QSettings>
#include <QStandardItemModel>
#include <QDebug>
#include "query.h"

Statistics::Statistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);

    //set up the lifetime table
    QStringList columnNames;
    columnNames += "Fillups";
    columnNames += "Miles";
    columnNames += "Gallons";
    columnNames += "Cost";
    columnNames += "MPG";

    //ui->lifetimeTable->setColumnCount(columnNames.size());
    //ui->lifetimeTable->setHorizontalHeaderLabels(columnNames);


    lifetimeModel = new QStandardItemModel(1,5,this);
    lifetimeModel->setHorizontalHeaderLabels(columnNames);
    lifetimeModel->setRowCount(0);
    lifetimeModel->setColumnCount(columnNames.size());

    //make the table not editable
    ui->lifetimeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //set the model
    ui->lifetimeTable->setModel(lifetimeModel);




    yearlyModel = new QStandardItemModel(this);
    yearlyModel->setHorizontalHeaderLabels(columnNames);
    yearlyModel->setRowCount(0);
    yearlyModel->setColumnCount(columnNames.size());

    //make the table not editable
    ui->yearTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //set the model
    ui->yearTable->setModel(yearlyModel);


//    for(int i=0;i<columnNames.size();i++)
//    {
//        //ui->lifetimeTable->model()->setHeaderData(i,Qt::Horizontal,columnNames.at(i));
//        qDebug()<<"column name:"<<columnNames.at(i);

//    }

    refreshAllStats();
    //lifetimeStats();


}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::refreshAllStats()
{
    lifetimeStats();
    yearlyStats();
}

void Statistics::lifetimeStats()
{
    //get vehicle id
    QSettings settings;
    int vehicleId = settings.value("config/vehicle").toInt();
    Query query;
    //fillups,miles,gallons,cost,mpg
    QList<QVariant> data = query.lifetimeStats(vehicleId);


    //get rid of all the current rows first
    lifetimeModel->removeRows(0,lifetimeModel->rowCount());

    //list of all the items for a row
    QList<QStandardItem*> items;
    //loop through the data
    //QString(QLocale().currencySymbol()+"%L1").arg(cost,0,'f',2);
    QStandardItem *fillups = new QStandardItem(data.at(0).toString());
    items.append(fillups);

    QStandardItem *miles = new QStandardItem(data.at(1).toString());
    items.append(miles);

    QStandardItem *gallons = new QStandardItem(data.at(2).toString());
    items.append(gallons);

    QString f = QLocale::system().currencySymbol();
    f.append((QLocale::system().toString(data.at(3).toDouble(),'f',2)));
    QStandardItem *cost = new QStandardItem(f);
    items.append(cost);

    f = "";
    f.append((QLocale::system().toString(data.at(4).toDouble(),'f',2)));
    QStandardItem *mpg = new QStandardItem(f);
    items.append(mpg);

    lifetimeModel->appendRow(items);

}

void Statistics::yearlyStats()
{
    //get vehicle id
    QSettings settings;
    int vehicleId = settings.value("config/vehicle").toInt();
    Query query;
    //fillups,miles,gallons,cost,mpg
    QList< QList<QVariant> > data = query.yearlyStats(vehicleId);

    //get rid of all the current rows first
    yearlyModel->removeRows(0,yearlyModel->rowCount());

    QStringList rowNames;
    //year,fillups,miles,gallons,cost,mpg

    for(int i=0;i<data.count();i++)
    {
        QList<QVariant> row = data.at(i);
        QList<QStandardItem*> forModel;
        QString year = row.at(0).toString();
        QStandardItem *fillups = new QStandardItem(row.at(1).toString());
        QStandardItem *miles = new QStandardItem(row.at(2).toString());
        QStandardItem *gallons = new QStandardItem(row.at(3).toString());
        QString f = QLocale::system().currencySymbol();
        f.append((QLocale::system().toString(row.at(4).toDouble(),'f',2)));
        QStandardItem *cost = new QStandardItem(f);

        f = "";
        f.append((QLocale::system().toString(row.at(5).toDouble(),'f',2)));
        QStandardItem *mpg = new QStandardItem(f);

        rowNames.append(year);
        forModel.append(fillups);
        forModel.append(miles);
        forModel.append(gallons);
        forModel.append(cost);
        forModel.append(mpg);

        yearlyModel->appendRow(forModel);

    }
    //set the row names to be the years
    yearlyModel->setVerticalHeaderLabels(rowNames);

    //try to fix the row color...
    for(int i=0;i<yearlyModel->rowCount();i++)
    {
        for (int j=0;j<yearlyModel->columnCount();j++)
        {
            if (i %2 ==0)
                yearlyModel->setData(yearlyModel->index(i,j),QColor(224,229,233),Qt::BackgroundRole);
            else
                yearlyModel->setData(yearlyModel->index(i,j),QColor(Qt::white),Qt::BackgroundRole);
        }
    }


}
