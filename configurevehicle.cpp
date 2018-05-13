#include "configurevehicle.h"
#include "query.h"
#include <QDebug>
#include <QSettings>
#include <QSqlError>
#include <QMessageBox>
#include "login.h"

ConfigureVehicle::ConfigureVehicle(QWidget *parent) : QWidget(parent)
{
    vehicleBase.setupUi(this);

    model = new VehicleModel();

    vehicleBase.tableView->setModel(model);

    //hide the first column since its the id
    vehicleBase.tableView->setColumnHidden(0,true);
    vehicleBase.tableView->resizeColumnsToContents();

    connect(vehicleBase.saveButton,SIGNAL(clicked()),this,SLOT(saveVehicle()));

    //refreshTable();
}

ConfigureVehicle::~ConfigureVehicle()
{
    delete model;
}

void ConfigureVehicle::saveVehicle()
{
    if (vehicleBase.description->text() != "")
    {
        qDebug()<<"save me:"<<vehicleBase.description->text();
        Query q;
        if(q.insertVehicle(vehicleBase.description->text()))
        {
            refreshTable();
            vehicleBase.description->setText("");
        }
        else
        {
            qDebug()<<"saveVehicle couldn't save";
        }

        //QSettings settings;
        //QString t = settings.value("config/databasetype").toString();
        //if(t == "sqlite")
        //{
            //Sqlite *con = (Sqlite*)owner->getConnection();
//            if (owner->getConnection()->insertVehicle(vehicleBase.description->text()))
//            {
//                vehicleBase.description->setText("");
//                qDebug()<<"inserted a new record";
//                refreshTable();

//            }
        //}
        //qDebug()<<this->parentWidget()->objectName();
        //first parent is configurebase
        //second parent is
    }
}

void ConfigureVehicle::refreshTable()
{
    //qDebug()<<"refresh the configurevehicle table";
    Query q;
    if (!q.selectVehicle(model))
    {
        //qDebug()<<"something happened with selectVehicle";
        QString p = "somethign happened with refreshTable selectVehicle: " + q.error();
        QMessageBox message(QMessageBox::Critical,"Problem!",p,QMessageBox::Ok,this,Qt::Dialog);
        message.exec();
    }
}

//void ConfigureVehicle::createModel()
//{
//    model = new VehicleModel();
//}

//void ConfigureVehicle::deleteModel()
//{
//    delete model;
//}
    //qDebug()<<"gonna call select";
    //reread the config file
    //QSqlDatabase db = QSqlDatabase::database();
//    QSettings settings;
//    QString type = settings.value("config/databasetype").toString();
//    if(type != "")
//    {
//        //qDebug()<<"config file type:"<<type;
//        if (type == "sqlite")
//        {
//            QString location = settings.value("config/location").toString();
//            QString filename = settings.value("config/filename").toString();
//            db = QSqlDatabase::addDatabase("QSQLITE");
//            db.setDatabaseName(location+"/"+filename);
//            if (db.open())
//            {
//                Query q;
//                if(!q.selectVehicle(model))
//                {
//                    QString error = "Couldn't get the vehicles!";
//                    QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
//                    message.exec();
//                }
//            }
//        }
//        else if (type == "mariadb")
//        {
//            QString hostname = settings.value("config/hostname").toString();
//            QString dbaseName = settings.value("config/dbasename").toString();
//            int port = settings.value("config/port").toInt();

//            //qDebug()<<"database name:"<<db.databaseName();
//            //qDebug()<<"driver name:"<<db.driverName();
//            if (db.driverName()!="QMYSQL")
//            {
//                db = QSqlDatabase::addDatabase("QMYSQL");
//                db.setHostName(hostname);
//                db.setDatabaseName(dbaseName);
//                db.setPort(port);
//                qDebug()<<"need to show the login dialog box and do all that good stuff here";
//                Login login;
//                if (login.exec())
//                {
//                    db.setUserName(login.getUsername());
//                    db.setPassword(login.getPassword());
//                    if (db.open())
//                        qDebug()<<"database is now open";
//                }
//            }
//        }
//        if (db.open())
//        {
//            Query q;
//            if(!q.selectVehicle(model))
//            {
//                QString error = "Couldn't get the vehicles!";
//                QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
//                message.exec();
//            }

//        }
//            {
//                Query q;
//                if(!q.selectVehicle(model))
//                {
//                    QString error = "Couldn't get the vehicles!";
//                    QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
//                    message.exec();
//                }

//            }

//            else if (!db.isOpen())
//            {
//                db.open();
//            }







//        db = QSqlDatabase::database();
//        qDebug()<<"driver name:"<<db.driverName();
//        qDebug()<<"connection name:"<<db.connectionName();
//        if (!db.isOpen())
//        {
//            db.open();
//            qDebug()<<db.lastError().text();
//        }
//        if (db.isOpen())
//        {
//            Query q;
//            if(!q.selectVehicle(model))
//            {
//                QString error = "Couldn't get the vehicles!";
//                QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
//                message.exec();
//            }
//        }

//    }


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


//}
