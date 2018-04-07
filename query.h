#ifndef QUERY_H
#define QUERY_H

#include "vehiclemodel.h"
#include "alldatamodel.h"

class QString;

class Query
{

public:
    Query();
    virtual void createVehicleTable(){};
    virtual void createMileageTable(){};

    bool insertVehicle(QString);
    bool selectVehicle(VehicleModel*);

    bool selectFuelMileage(int, AllDataModel *);

};

#endif // QUERY_H
