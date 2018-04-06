#include "configurevehicle.h"
//#include "query.h"
#include "sqlite.h"
#include <QDebug>

ConfigureVehicle::ConfigureVehicle(QWidget *parent) : QWidget(parent)
{
    vehicleBase.setupUi(this);
    owner = (MainWindow*)parent;

    QSettings settings;
    QString t = settings.value("config/databasetype").toString();
    qDebug()<<t;

    model = new VehicleModel();

    vehicleBase.tableView->setModel(model);
    //model->setTable("vehicles");
    //model->select();

    //vehicleBase.tableView->setColumnHidden(0,true);
    //vehicleBase.tableView->resizeColumnsToContents();


    //refreshTable();

//    if(t == "sqlite")
//    {
//        model = new VehicleDisplayModel(owner);
//        vehicleBase.tableView->setModel(model);
//        model->setTable("vehicles");
//        model->select();

//        vehicleBase.tableView->setColumnHidden(0,true);
//        vehicleBase.tableView->resizeColumnsToContents();
//    }

    connect(vehicleBase.saveButton,SIGNAL(clicked()),this,SLOT(saveVehicle()));
}

ConfigureVehicle::~ConfigureVehicle()
{
    delete model;
}

void ConfigureVehicle::saveVehicle()
{
    if (vehicleBase.description->text() != "")
    {
        //qDebug()<<"save me:"<<vehicleBase.description->text();

        QSettings settings;
        QString t = settings.value("config/databasetype").toString();
        if(t == "sqlite")
        {
            //Sqlite *con = (Sqlite*)owner->getConnection();
            if (owner->getConnection()->insertVehicle(vehicleBase.description->text()))
            {
                vehicleBase.description->setText("");
                qDebug()<<"inserted a new record";
                refreshTable();

            }
        }
        //qDebug()<<this->parentWidget()->objectName();
        //first parent is configurebase
        //second parent is
    }
}

void ConfigureVehicle::refreshTable()
{
    qDebug()<<"gonna call select";
    //model->setTable("vehicles");
    //model->clear();
    //model->select();
}
