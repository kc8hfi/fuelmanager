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
        qDebug()<<"exec is ok here";
    }
    else
    {
        qDebug()<<"wrong:"<<q.lastError().text();
    }






//    qDebug()<<"after qsqlquery: "<<s;
//    q.prepare(s);
//    qDebug()<<"after prepare: "<<s;

//    qDebug()<<"db open? "<<db.isOpen();
//    if(q.exec())
//    {
//        ok = true;
//        //need a couple colors to switch between
//        QColor one = Qt::white;
//        QColor two = Qt::lightGray;
//        int i=0;
//        while(q.next())
//        {
//            Vehicle v;
//            v.id = q.value(0).toInt();
//            v.description = q.value(1).toString();

//            //alternate the row colors
//            if(i %2 == 0)
//            {
//                model->addColor(one);
//            }
//            else
//            {
//                model->addColor(two);
//            }
//            model->insertRow(model->rowCount(QModelIndex()),1,QModelIndex(),v);
//            i++;
//        }
//    }
//    else
//        qDebug()<<"error trying to exec selectvehicle: "<<q.lastError().text();

    return ok;
}
