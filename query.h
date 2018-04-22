#ifndef QUERY_H
#define QUERY_H

#include "vehiclemodel.h"
#include "alldatamodel.h"

class Query
{
public:
    Query();
    void createVehicleTable();
    void createMileageTable();

    bool insertVehicle(QString);
    bool selectVehicle(VehicleModel*);
    void updateVehicle(Vehicle);

    bool updateFuelMileage(QList<Mileage>t);

    QString getVehicleDescription(int);

    bool selectFuelMileage(int, AllDataModel *);
    bool insertFuelMileage(int,double,double,double,QString);

    QList<QVariant> lifetimeStats(int);

private:

};


#endif //QUERY_H
