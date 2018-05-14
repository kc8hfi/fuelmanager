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


    monthNames["01"] = "January";
    monthNames["02"] = "February";
    monthNames["03"] = "March";
    monthNames["04"] = "April";
    monthNames["05"] = "May";
    monthNames["06"] = "June";
    monthNames["07"] = "July";
    monthNames["08"] = "August";
    monthNames["09"] = "September";
    monthNames["10"] = "October";
    monthNames["11"] = "November";
    monthNames["12"] = "December";

    QStringList monthlyColNames;

    QMapIterator<QString,QString> i(monthNames);
    while (i.hasNext())
    {
        i.next();
        monthlyColNames.append(i.value());
    }
    monthlyModel = new QStandardItemModel(this);
    monthlyModel->setHorizontalHeaderLabels(monthlyColNames);
    monthlyModel->setRowCount(0);
    monthlyModel->setColumnCount(monthlyColNames.size());

    //make table not editable
    ui->monthTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //set the mode
    ui->monthTable->setModel(monthlyModel);

}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::refreshAllStats(int id)
{
    lifetimeStats(id);
    yearlyStats(id);
    monthlyStats(id);
}

void Statistics::lifetimeStats(int vehicleId)
{
    //get vehicle id
    Query query;
    //fillups,miles,gallons,cost,mpg
    QList<QVariant> data = query.lifetimeStats(vehicleId);
    if (data.count() >0)
    {
        //get rid of all the current rows first
        lifetimeModel->removeRows(0,lifetimeModel->rowCount());

        //list of all the items for a row
        QList<QStandardItem*> items;
        //loop through the data
        //QString(QLocale().currencySymbol()+"%L1").arg(cost,0,'f',2);
        QStandardItem *fillups = new QStandardItem(data.at(0).toString());
        items.append(fillups);

        QStandardItem *miles = new QStandardItem(QLocale::system().toString(data.at(1).toDouble(),'f',2));
        items.append(miles);

        QStandardItem *gallons = new QStandardItem(QLocale::system().toString(data.at(2).toDouble(),'f',2));
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

}

void Statistics::yearlyStats(int vehicleId)
{
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
        QStandardItem *miles = new QStandardItem(QLocale::system().toString(row.at(2).toDouble(),'f',2));
        QStandardItem *gallons = new QStandardItem(QLocale::system().toString(row.at(3).toDouble(),'f',2));
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
}//end yearlyStats

void Statistics::monthlyStats(int vehicleId)
{
    Query query;

    //get rid of all the current rows first
    monthlyModel->removeRows(0,monthlyModel->rowCount());

    //get the years first
    QList<QVariant> years = query.getDistinctYears(vehicleId);

    //loop through the years
    for(int i=0;i<years.count();i++)
    {
        QList<QStandardItem*> forModel;
        QMapIterator<QString,QString> j(monthNames);
        while (j.hasNext())
        {
            j.next();
            //if (i==0 && j.key() == "02")
            QList<QVariant> d = query.monthlyStats(vehicleId,years.at(i),j.key());
            QString s = "";
            if (d.at(0).toInt() != 0)
            {
                s += "Fillups: " + d.at(0).toString() + "\n";
                s += "Miles: " + QLocale::system().toString(d.at(1).toDouble(),'f',2) + "\n";
                s += "Gallons: " + QLocale::system().toString(d.at(2).toDouble(),'f',2) + "\n";
                s += "Cost:" + QLocale::system().currencySymbol();
                s += QLocale::system().toString(d.at(3).toDouble(),'f',2) + "\n";
                s += "MPG: " + QLocale::system().toString(d.at(4).toDouble(),'f',2);
            }
            QStandardItem *item = new QStandardItem(s);
            forModel.append(item);
        }
        monthlyModel->appendRow(forModel);
    }//end year loop


    QStringList rowNames;
    for(int i=0;i<years.count();i++)
    {
        rowNames.append(years.at(i).toString());
    }
    monthlyModel->setVerticalHeaderLabels(rowNames);


    //resize the columns to the contents
    ui->monthTable->resizeColumnsToContents();
    //resize rows to the contents
    ui->monthTable->resizeRowsToContents();

    //try to fix the row color...
    for(int i=0;i<monthlyModel->rowCount();i++)
    {
        for (int j=0;j<monthlyModel->columnCount();j++)
        {
            if (i %2 ==0)
                monthlyModel->setData(monthlyModel->index(i,j),QColor(224,229,233),Qt::BackgroundRole);
            else
                monthlyModel->setData(monthlyModel->index(i,j),QColor(Qt::white),Qt::BackgroundRole);
        }
    }
}//end monthlyStats
