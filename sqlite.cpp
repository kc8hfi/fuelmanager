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
#include "alldatamodel.h"

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
    QSqlQuery q(QSqlDatabase::database());
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
    //QSqlQuery q(s);
    QSqlQuery q(QSqlDatabase::database());
    //qDebug()<<"i'm guessing theres no database connection here";
    q.prepare(s);
    q.bindValue(":id",i);
    QString desc = "";
    if (q.exec())
    {
        if (q.next())
        {
            //qDebug()<<"next failed here";
            desc = q.value(0).toString();
            //qDebug()<<"crashed right before this";
        }
    }
    else
    {
        QString error = q.lastError().text();
        //QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
        //message.exec();
    }
    //qDebug()<<"returning:"<<desc;
    return desc;
}

bool Sqlite::insertFuelMileage(int id,double miles,double gallons,double cost,QString date)
{
    QString s = "insert into fuel_mileage (miles,gallons,cost,fillup_date,vehicle_id)\
        values(:miles,:gallons,:cost,:date,:id) ";
    QSqlQuery query(QSqlDatabase::database());
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
        //qDebug()<<"insertFuelMileage:"<<query.lastError().text();
        QString error = "insertFuelMileage\n"+query.lastError().text();
        QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,(QWidget*)owner,Qt::Dialog);
        message.exec();
        //QMessageBox::warning(owner,"getVehidledesc","something bad",QMessageBox::Ok);

    }
    return ok;
}
bool Sqlite::selectFuelMileage(int vehicleId, AllDataModel *model)
{
    QString s = "select id,miles,gallons,cost,fillup_date \
            from fuel_mileage \
            where vehicle_id = :id \
            order by fillup_date desc ";

    QSqlQuery query(QSqlDatabase::database());

    query.prepare(s);
    query.bindValue(":id",vehicleId);
    bool ok = false;

    qDebug()<<"row count:"<<model->rowCount(QModelIndex());
    if (query.exec())
    {
        ok = true;
        while(query.next())
        {
            Mileage m;
            m.id = query.value(0).toInt();
            m.miles = query.value(1).toDouble();
            m.gallons = query.value(2).toDouble();
            m.cost = query.value(3).toDouble();
            m.date = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");

            qDebug()<<m.id<<m.miles<<m.gallons<<m.cost<<m.date;
//            model->insertRows(0,1,QModelIndex());
//            QModelIndex index = model->index(0,0,QModelIndex());
//            model->setData(index,m.id,Qt::EditRole);

//            index = model->index(0,1,QModelIndex());
//            model->setData(index,m.miles,Qt::EditRole);

//            index = model->index(0,2,QModelIndex());
//            model->setData(index,m.gallons,Qt::EditRole);

//            index = model->index(0,3,QModelIndex());
//            model->setData(index,m.cost,Qt::EditRole);

//            index = model->index(0,4,QModelIndex());
//            model->setData(index,m.date,Qt::EditRole);

        }
    }
    else
    {
        qDebug()<<"problemhere:"<<query.lastError().text();
    }
    //qDebug()<<"selectFuelMileage, how many records"<<d.size();
    return ok;
}
