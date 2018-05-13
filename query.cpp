#include "query.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSettings>
#include <QDebug>

Query::Query()
{
    //createVehicleTable();
    //createMileageTable();
}

void Query::createVehicleTable()
{
    QString queryString = "";
    QSettings settings;
    QString type = settings.value("config/databasetype").toString();
    if(type == "sqlite")
    {
        queryString = "create table if not exists vehicles \
                (id integer primary key on conflict fail autoincrement, \
                description text)";
    }
    else if(type =="mariadb")
    {
        queryString = "create table if not exists vehicles (\
            id int(11) not null auto_increment, \
            description varchar(255) default null, \
            primary key (id) \
            ) engine=innodb default charset=latin1 \
            ";
    }
    QSqlDatabase db = QSqlDatabase::database(type);
    if (db.isOpen())
    {
        QSqlQuery query(queryString,db);
        if (!query.isActive())
        {
            qDebug()<<"create vehicle table failed:"<<"dbase type:"<<type<<":"<<query.lastError().text()
                   <<query.lastQuery();
            errorMessage = "createVehicleTable query problem: " + query.lastError().text();
        }
    }
    else
    {
        errorMessage = "createVehicleTable db problem: " + db.lastError().text();
    }
}

void Query::createMileageTable()
{
    QString queryString = "";
    QSettings settings;
    QString type = settings.value("config/databasetype").toString();
    if(type == "sqlite")
    {
        queryString = "create table if not exists fuel_mileage \
                (id integer primary key on conflict fail autoincrement, \
                miles real, \
                gallons real, \
                cost real, \
                fillup_date text, \
                vehicle_id integer not null, \
                foreign key (vehicle_id) references vehicle(id) \
        )";
    }
    else if(type =="mariadb")
    {
        queryString = "create table if not exists fuel_mileage (\
            id int(11) not null auto_increment, \
            miles double default null, \
            gallons double default null, \
            cost double default null, \
            fillup_date date default null, \
            vehicle_id int(11) default null, \
            primary key (id), \
            key vehicle_id_fk (vehicle_id), \
            constraint vehicle_id_fk foreign key (vehicle_id) \
            references vehicles(id) on delete no action on update no action )\
            engine=innodb default charset=latin1 \
            ";
    }
    QSqlDatabase db = QSqlDatabase::database(type);
    if (db.isOpen())
    {
        QSqlQuery query(queryString,db);
        if (!query.isActive())
        {
            qDebug()<<"create fuel_mileage table failed:"<<query.lastError().text()
                   <<query.lastQuery();
            errorMessage = "createMileageTable query problem: " + query.lastError().text();
        }
    }
    else
    {
        errorMessage = "createMileageTable db problem: " + db.lastError().text();
    }
}


bool Query::insertVehicle(QString n)
{
    bool ok = false;
    QString str = "insert into vehicles (description) values (:description)";
    QSettings settings;
    QString type = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(type);
    if (db.isOpen())
    {
        QSqlQuery q(str, db);
        q.prepare(str);
        q.bindValue(":description",n);
        if (q.exec())
        {
            ok = true;
        }
        else
        {
            //qDebug()<<q.lastError().text();
            errorMessage = "insertVehicle query problem: " + q.lastError().text();
        }
    }
    else
    {
        errorMessage = "insertVehicle db problem: " + db.lastError().text();
    }
    return ok;
}

void Query::updateVehicle(Vehicle v)
{
    QString queryString = "update vehicles set description = :desc where id = :id";
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        QSqlQuery q(db);
        q.prepare(queryString);
        q.bindValue(":desc",v.description);
        q.bindValue(":id",v.id);
        if(!q.exec())
        {
            qDebug()<<"updateVehicle query problem:  " + q.lastError().text();
            errorMessage = "updateVehicle query problem:  " + q.lastError().text();
        }
    }
    else
    {
        errorMessage = "updateVehicle db problem: " + db.lastError().text();
    }
}

bool Query::selectVehicle(VehicleModel *model)
{
    bool ok = false;
    //empty out the model first
    model->removeRows(0,model->rowCount(QModelIndex()));
    QString s = "select id,description from vehicles";

    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);
    QSqlQuery q(s,db);
    if (db.isOpen())
    {
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
        {
            //qDebug()<<"error trying to exec selectvehicle: "<<q.lastError().text();
            errorMessage = "selectVehicle query problem:  " + q.lastError().text();
        }
    }
    else
    {
        errorMessage = "selectVehicle db problem: " + db.lastError().text();
    }
    return ok;
}

bool Query::selectFuelMileage(int vehicleId, AllDataModel *model)
{
    bool ok = false;
    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QString s = "select id,fillup_date,miles,gallons,cost,miles/gallons as mpg \
            from fuel_mileage \
            where vehicle_id = :id \
            order by fillup_date desc ";

    QSqlQuery query(s,db);
    if (db.isOpen())
    {
        query.prepare(s);
        query.bindValue(":id",vehicleId);

        //qDebug()<<"row count:"<<model->rowCount(QModelIndex());
        if (query.exec())
        {
            ok = true;

            //need a couple colors to switch between
            QColor one = Qt::white;
            //QColor two = Qt::lightGray;
            QColor two(215, 238, 247);
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
            //qDebug()<<"problemhere:"<<query.lastError().text();
            errorMessage = "selectFuelMileage query problem: " + query.lastError().text();
        }
    }
    else
    {
        errorMessage = "selectFuelMileage db problem: " + db.lastError().text();
    }
    return ok;
}

QString Query::getVehicleDescription(int i)
{
    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QString desc = "";
    QString s = "select description from vehicles where id = :id";
    QSqlQuery q(s,db);
    if (db.isOpen())
    {
        //qDebug()<<"i'm guessing theres no database connection here";
        q.prepare(s);
        q.bindValue(":id",i);
        if (q.exec())
        {
            if (q.next())
            {
                desc = q.value(0).toString();
            }
        }
        else
        {
            errorMessage = "getVehicleDescription query problem: " + q.lastError().text();
            //QString error = q.lastError().text();
            //QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,this,Qt::Dialog);
            //message.exec();
        }
    }
    else
    {
        errorMessage = "getVehicleDescription db problem: " + db.lastError().text();
    }
    return desc;
}


bool Query::insertFuelMileage(int id,double miles,double gallons,double cost,QString date)
{
    bool ok = false;
    QString s = "insert into fuel_mileage (miles,gallons,cost,fillup_date,vehicle_id)\
        values(:miles,:gallons,:cost,:date,:id) ";

    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QSqlQuery query(s,db);
    if (db.isOpen())
    {
        query.prepare(s);
        query.bindValue(":id",id);
        query.bindValue(":miles",miles);
        query.bindValue(":gallons",gallons);
        query.bindValue(":cost",cost);
        query.bindValue(":date",date);
        if(query.exec())
        {
            ok = true;
        }
        else
        {
            errorMessage = "insertFuelMileage query problem: " + query.lastError().text();
            //qDebug()<<"insertFuelMileage:"<<query.lastError().text();
    //        QString error = "insertFuelMileage\n"+query.lastError().text();
    //        QMessageBox message(QMessageBox::Critical,"Problem!",error,QMessageBox::Ok,(QWidget*)owner,Qt::Dialog);
    //        message.exec();
            //QMessageBox::warning(owner,"getVehidledesc","something bad",QMessageBox::Ok);

        }
    }
    else
    {
        errorMessage = "insertFuelMileage db problem: " + db.lastError().text();
    }
    return ok;
}

bool Query::updateFuelMileage(QList<Mileage>t)
{
    bool ok = false;

    QString q = "update fuel_mileage set  \
                       miles = :miles, \
                       gallons = :gallons, \
                       cost = :cost, \
                       fillup_date = :fillup_date \
                       where id = :id \
                       ";
    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);
    QSqlQuery query(q,db);

    if (db.isOpen())
    {
        query.prepare(q);
        for(int i=0;i<t.size();i++)
        {
            auto m = t.at(i);
            //qDebug()<<"id:"<<m.id<<" miles:"<<m.miles<<" gallons:"<<m.gallons;
            query.bindValue(":id",m.id);
            query.bindValue(":miles",m.miles);
            query.bindValue(":gallons",m.gallons);
            query.bindValue(":cost",m.cost);
            query.bindValue(":fillup_date",m.date.toString("yyyy-MM-dd"));
            if (!query.exec())
            {
                errorMessage = "updateFuelMileage query problem: " + query.lastError().text();
            }
//            else
//            {
//                qDebug()<<"id:"<<m.id<<" miles:"<<m.miles<<" gallons:"<<m.gallons<<" cost:"<<m.cost<<" date:"<<m.date.toString("yyyy-MM-dd");
//            }
        }
        ok = true;
    }
    else
    {
        //qDebug()<<"something wrong in updateFuelMileage";
        errorMessage = "updateFuelMileage db problem: " + db.lastError().text();
    }
    return ok;
}

QList<QVariant> Query::lifetimeStats(int id)
{
    QList<QVariant> stuff;
    QString q = "select sum(miles), \
            sum(gallons), \
            sum(cost) \
            from fuel_mileage \
            where vehicle_id = :id";
    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);
    QSqlQuery query(q,db);

    if (db.isOpen())
    {
        query.prepare(q);
        query.bindValue(":id",id);
        if (query.exec())
        {
            query.next();
            QSqlRecord record = query.record();
            for (int i=0; i<record.count();i++)
            {
                stuff.append(record.value(i));
                //qDebug()<<record.value(i);
            }

            if (stuff.at(1).toDouble() !=0.0)
                stuff.append(stuff.at(0).toDouble()/stuff.at(1).toDouble());  //mpg
            else
                stuff.append("0");

            //miles,gallons,cost,mpg
        }
        else
            qDebug()<<"lifetimeStats: "<<query.lastError().text();

        q = "select count(*)\
            from fuel_mileage \
            where vehicle_id = :id";
        query.prepare(q);
        query.bindValue(":id",id);
        if (query.exec())
        {
            query.next();
            stuff.prepend(query.value(0));
        }
    }
    else
    {
        qDebug()<<"lifetimeStats:  "<<db.lastError().text();
        errorMessage = "lifetimeStats db problem:" + db.lastError().text();
    }
//    for(int i=0;i<stuff.size();i++)
//    {
//        qDebug()<<"end lifetimeStats loop"<<stuff.at(i);
//    }

    //fillups,miles,gallons,cost,mpg
    return stuff;
}

QList< QList<QVariant> > Query::yearlyStats(int id)
{
    QList< QList<QVariant>> everything;
    QString q = "select strftime(\"%Y\",fillup_date) tyear,\
            count(id) ,\
               sum(miles) Miles,\
               sum(gallons) Gallons,\
               sum(cost) Cost\
               from fuel_mileage\
               where vehicle_id = :id\
               and strftime(\"%Y\",fillup_date) != '0000'\
               group by tyear\
               order by tyear desc";
    //qDebug()<<q;

    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QSqlQuery query(q,db);

    if (db.isOpen())
    {
        query.prepare(q);
        query.bindValue(":id",id);
        if (query.exec())
        {
            while(query.next())
            {
                QList<QVariant> stuff;
                QSqlRecord r = query.record();
                stuff.append(r.value(0));   //year
                stuff.append(r.value(1));   //fillups
                stuff.append(r.value(2));   //miles
                stuff.append(r.value(3));   //gallons
                stuff.append(r.value(4));   //cost

                if (stuff.at(3).toDouble()!= 0.0)
                    stuff.append(stuff.at(2).toDouble()/stuff.at(3).toDouble());
                else
                    stuff.append("0");

                //put this little qlist onto the big qlist
                everything.append(stuff);
            }//end while loop
        }//query executed successfully
        else
        {
            errorMessage = "yearlyStats query problem: " + query.lastError().text();
        }
    }//end db is open
    else
    {
        errorMessage = "yearlyStats db problem: " + db.lastError().text();
    }

    //year,fillups,miles,gallons,cost,mpg
    return everything;
}

QList<QVariant> Query::getDistinctYears(int id)
{
    QList<QVariant>stuff;
    QString q = "select distinct(strftime(\"%Y\",fillup_date)) theyear \
            from fuel_mileage \
            where vehicle_id = :id \
            and strftime(\"%Y\",fillup_date) != '0000'";
    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QSqlQuery query(q,db);

    if (db.isOpen())
    {
        query.prepare(q);
        query.bindValue(":id",id);
        if (query.exec())
        {
            while(query.next())
            {
                stuff.append(query.record().value(0));
            }
        }
    }
    return stuff;
}

QList<QVariant> Query::monthlyStats(int id,QVariant year,QVariant month)
{
    QList<QVariant>stuff;
    QString q = "select count(id),sum(miles),sum(gallons),sum(cost) from fuel_mileage where vehicle_id = :id \
and strftime(\"%Y\",fillup_date) = :year and strftime(\"%m\",fillup_date) = :month ";

    QSettings settings;
    QString dbaseType = settings.value("config/databasetype").toString();
    QSqlDatabase db = QSqlDatabase::database(dbaseType);

    QSqlQuery query(q,db);

    if (db.isOpen())
    {
        query.prepare(q);
        query.bindValue(":id",id);
        query.bindValue(":year",year.toString());
        query.bindValue(":month",month.toString());
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord r = query.record();
                int howmany = r.value(0).toInt();
                if (howmany != 0)   //they have fillups
                {
                    stuff.append(r.value(0));   //fillups
                    stuff.append(r.value(1));   //miles
                    stuff.append(r.value(2));   //gallons
                    stuff.append(r.value(3));   //cost
                    if (r.value(2).toDouble() != 0.0)
                        stuff.append(r.value(1).toDouble()/r.value(2).toDouble());  //mpg
                    else
                        stuff.append("0");  //mpg
                }
                else    //otherwise, nothing for this month/year combo
                {
                    stuff.append("0");  //fillups
                    stuff.append("0");  //miles
                    stuff.append("0");  //gallons
                    stuff.append("0");  //cost
                    stuff.append("0");  //mpg
                }
            }
        }//end exec
    }//end db is open
    return stuff;
}


QString Query::error()
{
    return errorMessage;
}
