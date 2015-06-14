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

#ifndef ALLDATA_H
#define ALLDATA_H

#include <QtSql>
//#include <QtGui>
#include "ui_alldata.h"
#include "mainwindow.h"

class QSqlDatabase;
class AllDataModel;
class CustomTable;
class QTableView;
class SortProxy;
class QAbstractItemView;

class AllData : public QWidget, private Ui_AllData_Base
{
     Q_OBJECT
     public:
          AllData(MainWindow *p);
          ~AllData();
     public slots:
          void refreshTable();
          void saveToDatabase ();
          void whichIndex (const QModelIndex & topLeft, const QModelIndex & bottomRight );

     private:
          Ui_AllData_Base everything;
          MainWindow *parent;
          AllDataModel *model;
          SortProxy *proxyModel;
          QList < QModelIndex > changedItems;
};

#endif //ALLDATA_H
