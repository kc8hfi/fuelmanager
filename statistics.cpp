#include "statistics.h"
#include "ui_statistics.h"
#include <QVBoxLayout>
#include <QSettings>
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
    columnNames += "MPG";
    columnNames += "Cost";

    ui->lifetimeTable->setColumnCount(columnNames.size());
    ui->lifetimeTable->setHorizontalHeaderLabels(columnNames);

    lifetimeStats();

}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::lifetimeStats()
{
    //get vehicle id
    QSettings settings;
    int vehicleId = settings.value("config/vehicle").toInt();
    Query query;
    QList<QVariant> data = query.lifetimeStats(vehicleId);

    //loop through the data
    for(int i=0;i<data.size();i++)
    {
        qDebug()<<data.at(i);
    }
}
