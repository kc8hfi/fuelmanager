/*!
 * Copyright 2008-2014 Charles Amey
 * 
 * This file is part of Fuel Manager.
 * 
 * Fuel Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Fuel Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Fuel Manager.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QString>
#include "databasequery.h"

#include <QDebug>

DatabaseQuery::DatabaseQuery()
{
}

DatabaseQuery::~DatabaseQuery()
{
}

QString DatabaseQuery::createVehicles(QString type)
{
     QString q = "";
     if (QString::compare(type, "sqlite") == 0)
     {
          q = "create table if not exists vehicles (id integer primary key on conflict fail autoincrement, ";
          q += "description text )";
     }
     else if (QString::compare(type, "mysql") == 0)
     {
          q = "create table if not exists vehicles (";
          q += "id int(11) not null auto_increment, ";
          q += "description varchar(100) default null,";
          q += "primary key (id) ";
          q += ") engine=innodb default charset=latin1 ";
     }
     return q;

}//end createVehicles

QString DatabaseQuery::createFuelMileage(QString type)
{
     QString q = "";
     if (QString::compare(type, "sqlite") == 0)
     {
          q = "create table if not exists fuel_mileage (id integer primary key on conflict fail autoincrement, ";
          q += "miles real,";
          q += "gallons real, ";
          q += "cost real, ";
          q += "fillup_date text, ";
          q += "vehicle_id integer not null, ";
          q += "foreign key (vehicle_id) references vehicles (id) ";
          q += ")";
     }
     else if (QString::compare(type, "mysql") == 0)
     {
          q = "create table if not exists fuel_mileage (";
          q += "id int(11) not null auto_increment, ";
          q += "miles double default null, ";
          q += "gallons double default null, ";
          q += "cost double default null, ";
          q += "fillup_date date default null, ";
          q += "vehicle_id int(11) default null, ";
          q += "primary key (id), ";
          q += "key vehicle_id_fk (vehicle_id), ";
          q += "constraint vehicle_id_fk foreign key (vehicle_id) ";
          q += "references vehicles (id) on delete no action on update no action )";
          q += "engine=innodb default charset=latin1";
     }
     
     return q;
}//end createFuelMileage

QString DatabaseQuery::getVehicleRecord()
{
     QString q = "";
     q = "select id,description from vehicles where id = :vehicleid";
     return q;
}//end getVehicleRecord     

QString DatabaseQuery::insertVehicle()
{
     QString q = "insert into vehicles (description) values (:description)";
     return q;
}

QString DatabaseQuery::insertFuelMileage()
{
     QString q = "insert into fuel_mileage (miles,gallons,cost,fillup_date, vehicle_id) \
                  values (:miles, :gallons, :cost, :fillup_date, :vehicleid)";
     return q;
}

QString DatabaseQuery::selectFuelMileage()
{
     QString q = "select id, miles,gallons,cost,fillup_date from fuel_mileage \
               where vehicle_id = :vehicleid \
               order by fillup_date desc";
     return q;
}

QString DatabaseQuery::updateFuelMileage()
{
     QString q = "update fuel_mileage set  \
                    miles = :miles, \
                    gallons = :gallons, \
                    cost = :cost, \
                    fillup_date = :fillupdate \
                    where id = :id \
                    ";
     return q;
}


