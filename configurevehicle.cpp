#include "configurevehicle.h"
//#include "query.h"
#include "sqlite.h"
#include <QDebug>
#include <QSettings>
#include <QSqlError>
#include <QMessageBox>

ConfigureVehicle::ConfigureVehicle(QWidget *parent) : QWidget(parent)
{
    vehicleBase.setupUi(this);

    QSettings settings;
    QString t = settings.value("config/databasetype").toString();
    qDebug()<<t;

    model = new VehicleModel();

    vehicleBase.tableView->setModel(model);

    //hide the first column since its the id
    vehicleBase.tableView->setColumnHidden(0,true);
    vehicleBase.tableView->resizeColumnsToContents();


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
//            if (owner->getConnection()->insertVehicle(vehicleBase.description->text()))
//            {
//                vehicleBase.description->setText("");
//                qDebug()<<"inserted a new record";
//                refreshTable();

//            }
        }
        //qDebug()<<this->parentWidget()->objectName();
        //first parent is configurebase
        //second parent is
    }
}

void ConfigureVehicle::refreshTable()
{
    qDebug()<<"gonna call select";
    //reread the config file
    QSqlDatabase db;
    QSettings settings;
    QString type = settings.value("config/databasetype").toString();
    if(type != "")
    {
        qDebug()<<"config file type:"<<type;
        if (type == "sqlite")
        {
            QString location = settings.value("config/location").toString();
            QString filename = settings.value("config/filename").toString();
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(location+"/"+filename);
        }

        db = QSqlDatabase::database();
        qDebug()<<"driver name:"<<db.driverName();
        qDebug()<<"connection name:"<<db.connectionName();
        if (!db.isOpen())
        {
            db.open();
            qDebug()<<db.lastError().text();
        }
        if (db.isOpen())
        {
            Query q;
            if(!q.selectVehicle(model))
            {
                QString error = "Couldn't get the vehicles!";
                QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
                message.exec();
            }
        }

    }


//    if (!owner->getConnection()->selectVehicle(model))
//    {

//    }



//    //get vehicle id
//    QSettings settings;
//    int vehicleId = settings.value("config/vehicle").toInt();
//    if(settings.value("config/databasetype").toString() == "sqlite")
//    {
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
//    }


}
