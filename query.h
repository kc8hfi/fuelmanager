#ifndef QUERY_H
#define QUERY_H

#include "vehiclemodel.h"

class QString;

class Query
{

public:
    Query();
    virtual void createVehicleTable(){};
    virtual void createMileageTable(){};

    bool insertVehicle(QString);
    bool selectVehicle(VehicleModel*);


};

#endif // QUERY_H
