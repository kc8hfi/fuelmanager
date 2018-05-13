#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include "selectvehicle.h"
#include "mainwindow.h"
#include "ui_selectvehicle.h"

SelectVehicle::SelectVehicle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectVehicle)
{
    ui->setupUi(this);

    QSettings settings;
    if(settings.contains("config/databasetype"))
    {
        QString dbaseType = settings.value("config/databasetype").toString();
        QSqlDatabase db = QSqlDatabase::database(dbaseType);

        if (db.open())
        {
            model = new VehicleDisplayModel(Q_NULLPTR,db);
            ui->tableView->setModel(model);

            model->setTable("vehicles");
            model->select();

            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->setColumnHidden(0,true);
            ui->tableView->resizeColumnsToContents();
        }
        else
        {
            //qDebug()<<"database is not open";
            QMessageBox mBox (QMessageBox::Critical, "Error in selecting a vehicle",
            db.lastError().text(), QMessageBox::Ok, this,Qt::Dialog);
            mBox.exec();
        }
    }

    //make the table clickable to select a vehicle
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickme()));

    //qDebug()<<"well, selectvehicle constructor is good";
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

    //qDebug()<<"bet it is crashing right here";
    //MainWindow *w = qobject_cast<MainWindow*>(QApplication::activeWindow());


    //update the label on the form
    //w->setVehicleName(n);
    //qDebug()<<"yep, crashed right about this line here";
    //refresh the alldata table
    //w->refreshAllData();

    emit accept();
}
