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
        qDebug()<<"insertFuelMileage:"<<query.lastError().text();
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
    if (query.exec())
    {
        ok = true;
        query.next();

        QColor one = Qt::lightGray;
        QColor two = Qt::darkCyan;

        one = Qt::white;
        two = Qt::lightGray;

        Mileage m;
        m.id = query.value(0).toInt();
        m.miles = query.value(1).toDouble();
        m.gallons = query.value(2).toDouble();
        m.cost = query.value(3).toDouble();
        m.date = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");



//        qDebug()<<"id:"<<query.value(0).toDouble();
//        qDebug()<<"miles:"<<query.value(1).toDouble();
//        qDebug()<<"gallons:"<<query.value(2).toDouble();
//        qDebug()<<"cost:"<<query.value(3).toDouble();
//        qDebug()<<"date:"<<query.value(4).toString();

        model->setModelData(m,one);

        int whichColor = 1;
        //now loop through the records
        while(query.next())
        {
//            qDebug()<<"this is the second row";
//            qDebug()<<"id:"<<query.value(0).toDouble();
//            qDebug()<<"miles:"<<query.value(1).toDouble();
//            qDebug()<<"gallons:"<<query.value(2).toDouble();
//            qDebug()<<"cost:"<<query.value(3).toDouble();
//            qDebug()<<"date:"<<query.value(4).toString();
            Mileage m;
            m.id = query.value(0).toInt();
            m.miles = query.value(1).toDouble();
            m.gallons = query.value(2).toDouble();
            m.cost = query.value(3).toDouble();
            m.date = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");
            if (whichColor == 1)
            {
                whichColor = 2;
                model->setModelData(m,two);
            }
            else if (whichColor == 2)
            {
                whichColor = 1;
                model->setModelData(m,one);
            }
        }
    }
    else
    {
        QString error = "selectFuelMileage\n"+query.lastError().text();
        QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,(QWidget*)owner,Qt::Dialog);
        message.exec();
    }
    return ok;
}
