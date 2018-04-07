#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QDebug>
#include "selectvehicle.h"
#include "mainwindow.h"
#include "ui_selectvehicle.h"

SelectVehicle::SelectVehicle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectVehicle)
{
    ui->setupUi(this);
    owner = (MainWindow*)parent;

    //QSettings settings;
    //QString t = settings.value("config/databasetype").toString();

    QSqlDatabase db = QSqlDatabase::database();
//    qDebug()<<"driver name:"<<db.driverName();
//    if (db.isOpen())
//        qDebug()<<"databse is open";


    model = new VehicleDisplayModel();
    ui->tableView->setModel(model);
    model->setTable("vehicles");
    model->select();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeColumnsToContents();


    //make the table clickable to select a vehicle
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickme()));

}

SelectVehicle::~SelectVehicle()
{
    delete ui;
}

void SelectVehicle::clickme()
{
    //qDebug()<<"clicked an item";
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndex current = selection->currentIndex();

    int i = current.row();
    QSqlRecord record = model->record(i);
    //qDebug()<<record.value(i);

    //save the vehicle to the config file
    QString n = record.value("description").toString();

    QSettings settings;
    settings.setValue("config/vehicle",record.value("id").toInt());

    //update the label on the form
    owner->setVehicleName(n);

    //refresh the alldata table
    owner->refreshAllData();
    qDebug()<<"refreshalldata should have been called";

    emit accept();
}
