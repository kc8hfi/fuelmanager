#ifndef QUERY_H
#define QUERY_H

#include "vehiclemodel.h"
#include "alldatamodel.h"

class Query
{
public:
    Query();
    virtual void createVehicleTable(){};
    virtual void createMileageTable(){};

    bool insertVehicle(QString);
    bool selectVehicle(VehicleModel*);

    QString getVehicleDescription(int);

    bool selectFuelMileage(int, AllDataModel *);
    bool insertFuelMileage(int,double,double,double,QString);


private:

};


#endif //QUERY_H
