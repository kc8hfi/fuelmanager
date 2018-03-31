#ifndef SELECTVEHICLE_H
#define SELECTVEHICLE_H

#include <QDialog>
#include "vehicledisplaymodel.h"

namespace Ui {
class SelectVehicle;
}

class SelectVehicle : public QDialog
{
    Q_OBJECT

public:
    explicit SelectVehicle(QWidget *parent = 0);
    ~SelectVehicle();

public slots:
    void clickme();

private:
    Ui::SelectVehicle *ui;
    MainWindow *owner;
    VehicleDisplayModel *model;
};

#endif // SELECTVEHICLE_H
