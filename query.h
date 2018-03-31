#ifndef QUERY_H
#define QUERY_H


class Query
{
public:
    Query();
    virtual void createVehicleTable(){};
    virtual void createMileageTable(){};
};

#endif // QUERY_H
