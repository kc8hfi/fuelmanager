#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QDebug>
#include "selectvehicle.h"
#include "mainwindow.h"
#include "ui_selectvehicle.h"

SelectVehicle::SelectVehicle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectVehicle)
{
    ui->setupUi(this);

    //QSettings settings;
    //QString t = settings.value("config/databasetype").toString();

    //QSqlDatabase db = QSqlDatabase::database();
    //qDebug()<<"selectvehicle constructor driver name:"<<db.driverName();

    model = new VehicleDisplayModel();
    ui->tableView->setModel(model);

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection", false);
    if (db.isOpen())
    {
        qDebug()<<"dbase name in here:"<<db.driverName();


        model->setTable("vehicles");
        qDebug()<<"error after set table"<<model->lastError();

        model->select();
        qDebug()<<"model select was ok";

        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->resizeColumnsToContents();

        qDebug()<<"set up the tableView for the vehicle selection";
    }
    else
    {
        qDebug()<<"databse isn't open to select vehicle";
    }
    //make the table clickable to select a vehicle
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickme()));

    qDebug()<<"well, selectvehicle constructor is good";
}

SelectVehicle::~SelectVehicle()
{
    delete ui;
}

void SelectVehicle::clickme()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndex current = selection->currentIndex();

    int i = current.row();
    QSqlRecord record = model->record(i);
    //qDebug()<<record.value(i);

    //save the vehicle to the config file
    QString n = record.value("description").toString();

    QSettings settings;
    settings.setValue("config/vehicle",record.value("id").toInt());

    qDebug()<<"bet it is crashing right here";
    //MainWindow *w = qobject_cast<MainWindow*>(QApplication::activeWindow());


    //update the label on the form
    //w->setVehicleName(n);
    //qDebug()<<"yep, crashed right about this line here";
    //refresh the alldata table
    //w->refreshAllData();

    emit accept();
}
