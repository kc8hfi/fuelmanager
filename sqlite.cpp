#include "sqlite.h"
#include <QSettings>
#include <QString>
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QWidget>

Sqlite::Sqlite(MainWindow *p)
{
    owner = p;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //qDebug()<<"at the beginnning";
    //qDebug()<<db.connectionName();

    QSettings settings;
    QString location = settings.value("config/location").toString();
    QString filename = settings.value("config/filename").toString();

    db.setDatabaseName(location+"/"+filename);
    QVERIFY(db.open());

    //QStringList list = QSqlDatabase::connectionNames();
    //qDebug()<<list.join(';');

    createVehicleTable();
    createMileageTable();
}

void Sqlite::createVehicleTable()
{
    QString str = QString("create table if not exists vehicles \
    (id integer primary key on conflict fail autoincrement, \
    description text)");
    QSqlQuery q(str);
    if (!q.isActive())
    {
        qDebug() << "Create vehicle table Fail: " << q.lastError().text()
                 << q.lastQuery();
    }
}

void Sqlite::createMileageTable()
{
    QString str = QString("create table if not exists fuel_mileage \
    (id integer primary key on conflict fail autoincrement, \
    miles real, \
    gallons real, \
    cost real, \
    fillup_date text, \
    vehicle_id integer not null, \
    foreign key (vehicle_id) references vehicle(id) )");
      QSqlQuery q(str);
      if (!q.isActive())
      {
          qDebug() << "Create fuel_mileage table Fail: " << q.lastError().text()
                   << q.lastQuery();
      }
}

bool Sqlite::insertVehicle(QString n)
{
    QString str = "insert into vehicles (description) values (:description)";
    QSqlQuery q(str);
    q.prepare(str);
    q.bindValue(":description",n);
    bool ok = false;
    if (q.exec())
    {
        ok = true;
    }
    else
    {
        qDebug()<<q.lastError().text();
    }
    return ok;
}

QString Sqlite::getVehicleDescription(int i)
{
    QString s = "select description from vehicles where id = :id";
    QSqlQuery q(s);
    q.prepare(s);
    q.bindValue(":id",i);
    QString desc = "";
    if (q.exec())
    {
        q.next();
        desc = q.value(0).toString();
    }
    else
    {
        QString error = q.lastError().text();
        //QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
        //message.exec();
    }
    return desc;
}

bool Sqlite::insertFuelMileage(int id,double miles,double gallons,double cost,QString date)
{
    QString s = "insert into fuel_mileage (miles,gallons,cost,fillup_date,vehicle_id)\
        values(:miles,:gallons,:cost,:date,:id) ";
    QSqlQuery query(s);
    query.prepare(s);
    query.bindValue(":id",id);
    query.bindValue(":miles",miles);
    query.bindValue(":gallons",gallons);
    query.bindValue(":cost",cost);
    query.bindValue(":date",date);
    bool ok = false;
    if(query.exec())
    {
        ok = true;
    }
    else
    {
        qDebug()<<"insertFuelMileage:"<<query.lastError().text();
        QString error = "insertFuelMileage\n"+query.lastError().text();
        QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,(QWidget*)owner,Qt::Dialog);
        message.exec();
        //QMessageBox::warning(owner,"getVehidledesc","something bad",QMessageBox::Ok);

    }
    return ok;
}
