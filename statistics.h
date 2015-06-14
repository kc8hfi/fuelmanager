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

#ifndef STATISTICS_H
#define STATISTICS_H
#include <QStringList>
//#include <QtGui>
#include <QTableView>
#include <QtSql>
#include "mainwindow.h"
#include "ui_statistics.h"

class QSqlDatabase;
class QTableWidget;
class MyModel;

class Statistics : public QWidget, private Ui_Statistics_Base
{
     Q_OBJECT
     public:
          Statistics(MainWindow *p);
          ~Statistics();
     public slots:
          void refreshTables();
     private:
          void lifetimeStats();
          void monthlyStats();
          void yearlyStats();
          
          MainWindow *parent;
          QTableWidget *lifetimeTable;
          QTableView *yearlyTable;
          QTableView *monthlyTable;
          QStringList columnNames;
          QMap<QString,QString> months;
          Ui_Statistics_Base statsBase;
          
          QColor one;
          QColor two;
          
          MyModel *model;
};

#endif //STATISTICS_H
