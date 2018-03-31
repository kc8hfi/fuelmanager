#ifndef SQLITE_H
#define SQLITE_H

#include "query.h"
#include <QSqlDatabase>
#include <QString>

class MainWindow;
class Sqlite : public Query
{
public:
    Sqlite(MainWindow*);
    void createVehicleTable();
    void createMileageTable();

    bool insertVehicle(QString);
    bool insertFuelMileage(int,double,double,double,QString);

    QString getVehicleDescription(int);
private:
    MainWindow *owner;
};

#endif // SQLITE_H
