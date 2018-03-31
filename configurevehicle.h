#ifndef CONFIGUREVEHICLE_H
#define CONFIGUREVEHICLE_H

#include <QWidget>
#include <QSqlTableModel>
#include "mainwindow.h"
#include "vehicledisplaymodel.h"
#include "ui_configurevehiclebase.h"


class ConfigureVehicle : public QWidget,private Ui_configureVehicleBase
{
    Q_OBJECT
public:
    explicit ConfigureVehicle(QWidget *parent = nullptr);

signals:

public slots:
    void saveVehicle();


private:
    Ui_configureVehicleBase vehicleBase;
    MainWindow *owner;
    VehicleDisplayModel *model;


};

#endif // CONFIGUREVEHICLE_H
