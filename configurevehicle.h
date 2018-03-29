#ifndef CONFIGUREVEHICLE_H
#define CONFIGUREVEHICLE_H

#include <QWidget>
#include "ui_configurevehicle.h"


class ConfigureVehicle : public QWidget,private Ui_configureVehicleBase
{
    Q_OBJECT
public:
    explicit ConfigureVehicle(QWidget *parent = nullptr);

signals:

public slots:


private:
    Ui_configureVehicleBase vehicleBase;
};

#endif // CONFIGUREVEHICLE_H
