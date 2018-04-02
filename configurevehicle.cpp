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
    if(t == "sqlite")
    {
        model = new VehicleDisplayModel(owner);
        vehicleBase.tableView->setModel(model);
        model->setTable("vehicles");
        model->select();

        vehicleBase.tableView->setColumnHidden(0,true);
        vehicleBase.tableView->resizeColumnsToContents();
    }

    connect(vehicleBase.saveButton,SIGNAL(clicked()),this,SLOT(saveVehicle()));
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
            Sqlite *con = (Sqlite*)owner->getConnection();
            if (con->insertVehicle(vehicleBase.description->text()))
            {
                vehicleBase.description->setText("");
            }
        }
        //qDebug()<<this->parentWidget()->objectName();
        //first parent is configurebase
        //second parent is
    }
}
