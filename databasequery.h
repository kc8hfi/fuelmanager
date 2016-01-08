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

#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

class QString;

class DatabaseQuery
{
     public:
          DatabaseQuery();
          ~DatabaseQuery();
          
          QString createVehicles(QString type);
          QString createFuelMileage(QString type);
          QString getVehicleRecord();
          QString insertVehicle();
          QString insertFuelMileage();
          QString selectFuelMileage();
          QString updateFuelMileage();
};


#endif  //DATABASEQUERY_H