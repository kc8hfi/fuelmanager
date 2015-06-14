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

#ifndef VEHICLEEDITMODEL_H
#define VEHICLEEDITMODEL_H

#include <QSqlTableModel>

class MainWindow;

class VehicleEditModel : public QSqlTableModel
{
     Q_OBJECT
     public:
          VehicleEditModel (MainWindow *p);
          ~VehicleEditModel();
          Qt::ItemFlags flags( const QModelIndex &index) const;
     private:
          MainWindow *parent;
};

#endif //VEHICLEEDITMODEL_H