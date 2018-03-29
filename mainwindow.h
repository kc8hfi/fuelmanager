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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include "ui_mainwindowbase.h"
#include "databasequery.h"

class AllData;
class Statistics;
class Assistant;

class MainWindow : public QMainWindow, private Ui_MainWindowBase
{
     Q_OBJECT
     public:
          MainWindow(QMainWindow *parent=0);
          ~MainWindow();
          void checkSettings();
          QSqlDatabase getConnection();
          QSqlRecord getVehicleRecord();
          DatabaseQuery* getQueries();

     private slots:
          void configure();
          void about();
          bool login ();
          void updateAllData ();
          void selectVehicle();
          void exportData();
          void help();
          void openConfigureDialog();
     private:
          void showEverything();
          void writeData(QString f);

          QSqlDatabase connection;
          DatabaseQuery *queries;
          QString whichDatabase;
          QString username;
          QString password;
          bool alreadyLoggedIn;

          QSqlRecord record;

          AllData *everything;
          Statistics *stats;
          
          Assistant *assistant;
          Ui_MainWindowBase mw;
};

#endif  //MAINWINDOW_H
