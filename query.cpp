#include "query.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Query::Query()
{

}


bool Query::insertVehicle(QString n)
{
    QString str = "insert into vehicles (description) values (:description)";
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = false;
    if (!db.isOpen())
    {
        db.open();
    }
    else
    {
        QSqlQuery q(db);
        q.prepare(str);
        q.bindValue(":description",n);
        if (q.exec())
        {
            ok = true;
        }
        else
        {
            qDebug()<<q.lastError().text();
        }
    }
    return ok;
}

bool Query::selectVehicle(VehicleModel *model)
{
    QString s = "select id,description from vehicles";
    QSqlDatabase db = QSqlDatabase::database();
    bool ok = false;
    QSqlQuery q(db);
    q.prepare(s);
    if(q.exec())
    {
        ok = true;
        //need a couple colors to switch between
        QColor one = Qt::white;
        QColor two = Qt::lightGray;
        int i=0;
        while(q.next())
        {
            Vehicle v;
            v.id = q.value(0).toInt();
            v.description = q.value(1).toString();

            //alternate the row colors
            if(i %2 == 0)
            {
                model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),v,one);
            }
            else
            {
                model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),v,two);
            }

            i++;
        }
    }
    else
        qDebug()<<"error trying to exec selectvehicle: "<<q.lastError().text();

    return ok;
}

bool Query::selectFuelMileage(int vehicleId, AllDataModel *model)
{
    QString s = "select id,fillup_date,miles,gallons,cost,miles/gallons as mpg \
            from fuel_mileage \
            where vehicle_id = :id \
            order by fillup_date desc ";

    QSqlQuery query(QSqlDatabase::database());

    query.prepare(s);
    query.bindValue(":id",vehicleId);
    bool ok = false;

    //qDebug()<<"row count:"<<model->rowCount(QModelIndex());
    if (query.exec())
    {
        ok = true;

        //need a couple colors to switch between
        QColor one = Qt::white;
        QColor two = Qt::lightGray;
        int whichColor=0;

        //hold the old month and year for comparison
        int oldmonth = 0;
        int oldyear = 0;

        //get the first row
        if (query.next())
        {
            Mileage f;
            f.id = query.value(0).toInt();
            f.date = QDate::fromString(query.value(1).toString(), "yyyy-MM-dd");
            f.miles = query.value(2).toDouble();
            f.gallons = query.value(3).toDouble();
            f.cost = query.value(4).toDouble();
            f.mpg = query.value(5).toDouble();

            oldmonth = f.date.month();
            oldyear = f.date.year();

            model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),f);
            model->addColor(one);
        }
        while(query.next())
        {
            Mileage m;
            m.id = query.value(0).toInt();
            m.date = QDate::fromString(query.value(1).toString(), "yyyy-MM-dd");
            m.miles = query.value(2).toDouble();
            m.gallons = query.value(3).toDouble();
            m.cost = query.value(4).toDouble();
            m.mpg = query.value(5).toDouble();

            //qDebug()<<m.id<<m.miles<<m.gallons<<m.cost<<m.date<<m.mpg;
            model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),m);

            //figure out what color this row is supposed to be
            if (oldmonth == m.date.month() && oldyear == m.date.year())
            {
                if(whichColor == 0)
                    model->addColor(one);
                else
                    model->addColor(two);
            }
            else
            {
                if(whichColor == 1)
                {
                    whichColor = 0;
                    model->addColor(one);
                }
                else
                {
                    whichColor = 1;
                    model->addColor(two);
                }
            }
            //keep the month and year for the next iteration
            oldmonth = m.date.month();
            oldyear = m.date.year();
        }//end while
    }
    else
    {
        qDebug()<<"problemhere:"<<query.lastError().text();
    }
    return ok;
}
