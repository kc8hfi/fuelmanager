#ifndef QUERY_H
#define QUERY_H


class QString;

class Query
{

public:
    Query();
    virtual void createVehicleTable(){};
    virtual void createMileageTable(){};

    bool insertVehicle(QString);
};

#endif // QUERY_H
