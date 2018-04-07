#ifndef SQLITE_H
#define SQLITE_H

#include "query.h"
#include <QSqlDatabase>
#include <QString>
#include "alldatamodel.h"

class MainWindow;


class Sqlite : public Query
{
public:
    Sqlite(MainWindow*);
    void createVehicleTable();
    void createMileageTable();

    //bool insertVehicle(QString);
    //bool insertFuelMileage(int,double,double,double,QString);

    //QString getVehicleDescription(int);

    //bool selectFuelMileage(int, AllDataModel*);
private:
    MainWindow *owner;
};

#endif // SQLITE_H
