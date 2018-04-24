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
    QList< QList<QVariant> > yearlyStats(int);


    QList<QVariant> getDistinctYears(int);
    QList<QVariant> monthlyStats(int,QVariant,QVariant);//vehicleId,years.at(i),i.key());

    //monthlyStats(int);

private:

};


#endif //QUERY_H
