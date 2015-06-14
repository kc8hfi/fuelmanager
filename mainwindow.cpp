/*!
 * Copyright 2008-2012 Charles Amey
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
 *
 */

#include <QSettings>
// #include <QSqlQuery>
// #include <QSqlError>
// #include <QVector>
#include <QDebug>
// #include <QtGui>
// #include <QtSql>
// #include <QIcon>

#include "about.h"
#include "alldata.h"
#include "configdialog.h"
#include "databasequery.h"
#include "entryform.h"
#include "login.h"
#include "mainwindow.h"
#include "selectvehicledialog.h"
#include "statistics.h"
#include "assistant.h"

MainWindow::MainWindow(QMainWindow *parent)
     :QMainWindow(parent)
{
     mw.setupUi(this);
     
     //set the icon
     //QString filename = "/usr/share/icons/hicolor/scalable/apps/fuelmanager.svg";
     QString filename = ":fuelmanager.svg";
     
     QFileInfo iconFilename(filename);
     if (iconFilename.exists())
     {
          QIcon icon(filename);
          setWindowIcon(icon);
     }
     
     //set up the basic info for qsettings
     QCoreApplication::setOrganizationName("fuelmanager");
     //QCoreApplication::setOrganizationDomain("homelinux.com");
     QCoreApplication::setApplicationName("fuelmanager");
     
     queries = new DatabaseQuery();
     
     whichDatabase = "";
     username = "";
     password = "";
     alreadyLoggedIn = false;
//      //check the settings
     checkSettings();
     
     //link up the about qt button
     connect(mw.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
     
     //link up the help button
     connect(mw.actionHelp,SIGNAL(triggered()), this, SLOT(help()));
     
     assistant = new Assistant;
     
     
}//end constructor

//destructor
MainWindow::~MainWindow()
{
     delete queries;
     //because it spawns a qprocess, we gotta kill it
     delete assistant;
}

//read the config file
void MainWindow::checkSettings()
{
     QSettings settings;
     QString databaseType = settings.value("config/databasetype").toString();
     QString savedVehicleId = settings.value("config/vehicle").toString();
     
     //qDebug()<<databaseType<<" "<<savedVehicleId;
     whichDatabase = databaseType;
     //check to see which database is selected
     if (databaseType == "")
     {
          //qDebug("no database in the config file, show config dialog");
          configure();
     }
     else if (databaseType == "sqlite")
     {
          //disable the login menu option
          mw.actionLogin->setEnabled(false);
          //check to make sure the tables are created
          QString dbaseLocation = settings.value("config/location").toString();
          QString dbaseFileName = settings.value("config/filename").toString();
          QString connectionName = settings.value("config/connection").toString();
          QString db = dbaseLocation + dbaseFileName;
          if (! QSqlDatabase::contains(connectionName))
          {
               QSqlDatabase::addDatabase("QSQLITE",connectionName);
          }
          connection = QSqlDatabase::database(connectionName,false);
          connection.setDatabaseName(db);
          
          if (connection.open())
          {
               //create vehicles
               QSqlQuery query(connection);
               QString q = queries->createVehicles(databaseType);
               query.exec(q);
               query.finish();
               
               //create fuel_mileage
               q = queries->createFuelMileage(databaseType);
               query.exec(q);
               query.finish();
          }
     }
     else if (databaseType == "mysql")
     {
          mw.actionLogin->setEnabled(true);
          connection.setHostName(settings.value("config/hostname").toString());
          connection.setDatabaseName(settings.value("config/dbasename").toString());
          connection.setPort(settings.value("config/port").toInt());
          QString connectionName = settings.value("config/connection").toString();
          if (! QSqlDatabase::contains(connectionName))
          {
               QSqlDatabase::addDatabase("QMYSQL",connectionName);
          }
          connection = QSqlDatabase::database(connectionName,false);
          if (!alreadyLoggedIn)
          {
               login();
          }
          if (connection.open(username,password))
          {
               //create vehicles table
               QSqlQuery query(connection);
               QString q = queries->createVehicles(databaseType);
               query.exec(q);
               query.finish();

               //create fuel_mileage table
               q = queries->createFuelMileage(databaseType);
               query.exec(q);
               query.finish();
               
          }//end connection is opened
          
          
     }//end database type is mysql
     
     //check for a saved vehicle
     if ( savedVehicleId != "")
     {
          if (connection.isOpen())
          {
               QString q = queries->getVehicleRecord();
               QSqlQuery query(connection);
               query.prepare(q);
               query.bindValue(":vehicleid",savedVehicleId);
               query.exec();
               query.next();
               record = query.record();
               showEverything();
          }
          else
          {
               QMessageBox mBox (QMessageBox::Critical, "Not logged in",
                    "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
               mBox.exec();
          }
     }
}//end checkSettings
// 
// //configuration 
void MainWindow::configure()
{
     //qDebug("show the configure dialog box");
     ConfigDialog configure(this);
     if (configure.exec())
     {
          //re-read the configuration file
          checkSettings();
     }
//   else
//   {
//        //checkSettings();
//        qDebug()<<"they just closed the configure dialog";
//   }
} //end configuration

QSqlDatabase MainWindow::getConnection()
{
     return connection;
}


// 
void MainWindow::showEverything()
{
     //remove all the tabs first
     mw.tabWidget->clear();
     if (connection.isOpen())
     {
          //set the vehicle description
          QString desc = record.value("description").toString();
          mw.vehicleLabel->setText(desc);

          //add the entry tab
          EntryForm *myEntryForm = new EntryForm(this);
          mw.tabWidget->addTab(myEntryForm,myEntryForm->windowTitle());
          
          //add the all data tab
          everything = new AllData(this);
          mw.tabWidget->addTab(everything, everything->windowTitle());

          //add the statistics tab
          stats = new Statistics(this);
          mw.tabWidget->addTab(stats,stats->windowTitle());
          
     }
     else
     {
          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
     }
}//end showEverything

QSqlRecord MainWindow::getVehicleRecord()
{
     return record;
}

DatabaseQuery* MainWindow::getQueries()
{
     return queries;
}

//show the about dialog
void MainWindow::about()
{
     About about;
     about.exec();
}

void MainWindow::help()
{
     assistant->showDocs("index.html");
}

//login dialog box
bool MainWindow:: login ()
{
     bool loginOk = false;
     
     QSettings settings;
     //read the config file
     connection.setHostName(settings.value("config/hostname").toString());
     connection.setDatabaseName(settings.value("config/dbasename").toString());
     connection.setPort(settings.value("config/port").toInt());
     Login mylogin;
     if (mylogin.exec())
     {
          username = mylogin.getUsername();
          password = mylogin.getPassword();
          //open the mysql dbase connection
          if (connection.open(username,password))
          {
               loginOk = true;
               alreadyLoggedIn = true;
          }
          else
          {
               loginOk = false;
               QMessageBox::warning(this,"Login Failed!", connection.lastError().text(),QMessageBox::Ok,0,0);
          }
     }
     else
     {
          loginOk = false;
     }
     return loginOk;
} //end login
 
void MainWindow::selectVehicle()
{
     //qDebug()<<"select vehicle dialog box goes here";
     //check and see if the database is open first
     if (connection.isOpen())
     {
          QSettings settings;
          SelectVehicleDialog choose(this);
          if (choose.exec())
          {
               record = choose.getRecord();
               settings.setValue("config/vehicle", record.value("id").toInt());
               showEverything();
          }
     }
     else
     {
          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
          
          mBox.exec();
     }
}//end selectVehicle
// 
//when tabs get clicked on, update the info on that particular tab
void MainWindow::updateAllData()
{
     if (mw.tabWidget->tabText(mw.tabWidget->currentIndex()) == "All Data")
     {
          everything->refreshTable();
     }
     else if (mw.tabWidget->tabText(mw.tabWidget->currentIndex()) == "Statistics")
     {
          stats->refreshTables();
     }
} //end updateAllData
// 
void MainWindow::exportData()
{
     //qDebug()<<"export the data for the currently selected vehicle";
     if (connection.isOpen())
     {
          QFileDialog dialog(this, tr("Save As..."));
          dialog.setFileMode(QFileDialog::AnyFile);
          dialog.setViewMode(QFileDialog::Detail);
          dialog.setDirectory(QDir::homePath()+"/");
          QStringList filename;
          if (dialog.exec())
          {
               filename = dialog.selectedFiles();
               if (filename[0] != "")
               {
                    //qDebug()<<filename[0];
                    if (QFile::exists(filename[0]))
                    {
                         QMessageBox message;
                         message.setText(tr("File already exists!"));
                         message.setInformativeText(tr("Overwrite?"));
                         message.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
                         message.setDefaultButton(QMessageBox::No);
                         //int value = message.exec();
                         if (message.exec() == QMessageBox::Yes)
                         {
                              //qDebug()<<"overwrite the file and write out the data";
                              writeData(filename[0]);
                         }
                    }//if file exists
                    else
                    {
                         //qDebug()<<"create file and write out the data";
                         writeData(filename[0]);
                    }
               }
          }//end dialog executed        
     }
     else
     {
          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
     }

}//end exportData();

void MainWindow::writeData(QString f)
{
     //create file to write to
     QFile file(f);
     file.open(QIODevice::WriteOnly|QIODevice::Text);
     QTextStream out(&file);  

     int vehicleId = record.value("id").toInt();

     QSqlQuery query(connection);
     QString q = queries->selectFuelMileage();
     query.prepare(q);
     query.bindValue(":vehicleid",vehicleId);
     if (query.exec())
     {
          out<<"\"id\",\"miles\",\"gallons\",\"cost\",\"fillup_date\""<<"\n";
          while(query.next())
          {
               QSqlRecord t = query.record();
               QString theData = "";
               for (int i=0;i<t.count();i++)
               {
                    theData = theData + "\"" + t.value(i).toString() + "\",";
               }
               theData = theData.remove(theData.length()-1,1);
               //qDebug()<<theData;
               out<<theData<<"\n";
          }//loop through resultset
          file.close();
          QMessageBox mBox (QMessageBox::Information, "Export Data",
               "Export is completed!", QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
          
     }//query was executed
}//end writeData
