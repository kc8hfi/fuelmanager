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
