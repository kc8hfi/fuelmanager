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
#include "query.h"

class AllData;
class EntryForm;
class Statistics;
//class Assistant;

class MainWindow : public QMainWindow, private Ui_MainWindowBase
{
     Q_OBJECT
     public:
          MainWindow(QMainWindow *parent=0);
          ~MainWindow();
          void checkSettings();

          //Query* getQuery();




          //void updateInterface();

          //QSqlDatabase getConnection();
          //QSqlRecord getVehicleRecord();
          //DatabaseQuery* getQueries();

     private slots:
          void configure();
          void selectVehicle();
          void about();

          void login();
          void updateAllData();
          void exportData();
          void help();



          //void about();
          //bool login ();
          //void updateAllData ();
          //void selectVehicle();
          //void exportData();
          //void help();
     private:
          //void showTabs();
            void setVehicleName();
            void updateInterface();
            void refreshAllData();

//          void vehicleName(int);
          //void writeData(QString f);
            Ui_MainWindowBase mw;

            QWidget *instructionsTab;

            EntryForm *entry;
            AllData *alldata;

            Statistics *stats;

//          Assistant *assistant;

};

#endif  //MAINWINDOW_H
