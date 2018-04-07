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
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>
#include <QTableView>
#include <QDesktopWidget>
#include <QSqlDatabase>
#include "configure.h"
#include "selectvehicle.h"
#include "entryform.h"
#include "about.h"
#include "alldata.h"

//#include "alldata.h"
//#include "configdialog.h"
//#include "databasequery.h"
//#include "entryform.h"
//#include "login.h"
//#include "selectvehicledialog.h"
//#include "statistics.h"
//#include "assistant.h"


#include "mainwindow.h"
#include "sqlite.h"


//#include "testwidget.h"

MainWindow::MainWindow(QMainWindow *parent)
     :QMainWindow(parent)
{
     mw.setupUi(this);


     QDesktopWidget *desktop = QApplication::desktop();

     int screenWidth, width;
     int screenHeight, height;
     int x, y;
     QSize windowSize;

     screenWidth = desktop->width(); // get width of screen
     screenHeight = desktop->height(); // get height of screen

     windowSize = size(); // size of our application window
     width = windowSize.width();
     height = windowSize.height();

     // little computations
     x = (screenWidth - width) / 2;
     y = (screenHeight - height) / 2;
     y -= 50;

     // move window to desired coordinates
     move ( x, y );





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
     
//     queries = new DatabaseQuery();
     
//     whichDatabase = "";
//     username = "";
//     password = "";
//     alreadyLoggedIn = false;


     //check the settings
     checkSettings();

     //link up the about qt button
     connect(mw.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
     
     //link up the help button
     connect(mw.actionHelp,SIGNAL(triggered()), this, SLOT(help()));
     
     //assistant = new Assistant;


     qDebug()<<"this is a qdebug";
     qWarning()<<"this is a qwarning";
     
}//end constructor

//destructor
MainWindow::~MainWindow()
{
     //delete queries;
     //because it spawns a qprocess, we gotta kill it
     //delete assistant;
}

Query* MainWindow::getQuery()
{
    return con;
}

//configuration
void MainWindow::configure()
{
//    Configure c;
//    c.exec();
    Configure *c = new Configure(this);
    c->show();

//    TestWidget *t = new TestWidget();
//    t->setParent(this);
//    t->show();
} //end configuration

void MainWindow::selectVehicle()
{
    qDebug()<<"show the select vehicle dialog box";
    SelectVehicle *s = new SelectVehicle(this);
    s->show();
}

void MainWindow::setVehicleName(QString s)
{
    mw.vehicleLabel->setText(s);
    //qDebug()<<"set the vehicle label to "<<s;
}

void MainWindow::vehicleName(int i)
{
    QSettings settings;
    QString t = settings.value("config/databasetype").toString();
    if (t == "sqlite")
    {
        Sqlite *c = (Sqlite*)con;
        QString name = c->getVehicleDescription(i);
        setVehicleName(name);
    }
}
//read the config file
void MainWindow::checkSettings()
{
     QSettings settings;
     QString databaseType = settings.value("config/databasetype").toString();
     if (databaseType == "sqlite")
     {
         //do we have a datase connection?
         QSqlDatabase db;
         if (db.driverName() == "")
         {
             QString location = settings.value("config/location").toString();
             QString filename = settings.value("config/filename").toString();
             db = QSqlDatabase::addDatabase("QSQLITE");
             db.setDatabaseName(location+"/"+filename);
             db.open();
         }
        //qDebug()<<"dbase driver name: "<<db.driverName();

     }
//     if (databaseType == "sqlite")
//     {
//         //disable the login action
//         mw.actionLogin->setEnabled(false);
//         con = new Sqlite(this);
//         vehicleName(settings.value("config/vehicle").toInt());
//     }
//     else if (databaseType == "mariadb")
//     {
//         mw.actionLogin->setEnabled(true);
//     }
     showTabs();

     QString savedVehicleId = settings.value("config/vehicle").toString();
     setVehicleName(savedVehicleId);
     
//     //qDebug()<<databaseType<<" "<<savedVehicleId;
//     whichDatabase = databaseType;
//     //check to see which database is selected
//     if (databaseType == "")
//     {
//          //qDebug("no database in the config file, show config dialog");
//          configure();
//     }
//     else if (databaseType == "sqlite")
//     {
//          //disable the login menu option
//          mw.actionLogin->setEnabled(false);
//          //check to make sure the tables are created
//          QString dbaseLocation = settings.value("config/location").toString();
//          QString dbaseFileName = settings.value("config/filename").toString();
//          QString connectionName = settings.value("config/connection").toString();
//          QString db = dbaseLocation + dbaseFileName;
//          if (! QSqlDatabase::contains(connectionName))
//          {
//               QSqlDatabase::addDatabase("QSQLITE",connectionName);
//          }
//          connection = QSqlDatabase::database(connectionName,false);
//          connection.setDatabaseName(db);
          
//          if (connection.open())
//          {
//               //create vehicles
//               QSqlQuery query(connection);
//               QString q = queries->createVehicles(databaseType);
//               query.exec(q);
//               query.finish();
               
//               //create fuel_mileage
//               q = queries->createFuelMileage(databaseType);
//               query.exec(q);
//               query.finish();
//          }
//     }
//     else if (databaseType == "mysql")
//     {
//          mw.actionLogin->setEnabled(true);
//          connection.setHostName(settings.value("config/hostname").toString());
//          connection.setDatabaseName(settings.value("config/dbasename").toString());
//          connection.setPort(settings.value("config/port").toInt());
//          QString connectionName = settings.value("config/connection").toString();
//          if (! QSqlDatabase::contains(connectionName))
//          {
//               QSqlDatabase::addDatabase("QMYSQL",connectionName);
//          }
//          connection = QSqlDatabase::database(connectionName,false);
//          if (!alreadyLoggedIn)
//          {
//               login();
//          }
//          if (connection.open(username,password))
//          {
//               //create vehicles table
//               QSqlQuery query(connection);
//               QString q = queries->createVehicles(databaseType);
//               query.exec(q);
//               query.finish();

//               //create fuel_mileage table
//               q = queries->createFuelMileage(databaseType);
//               query.exec(q);
//               query.finish();
               
//          }//end connection is opened
          
          
//     }//end database type is mysql
     
//     //check for a saved vehicle
//     if ( savedVehicleId != "")
//     {
//          if (connection.isOpen())
//          {
//               QString q = queries->getVehicleRecord();
//               QSqlQuery query(connection);
//               query.prepare(q);
//               query.bindValue(":vehicleid",savedVehicleId);
//               query.exec();
//               query.next();
//               record = query.record();
//               showEverything();
//          }
//          else
//          {
//               QMessageBox mBox (QMessageBox::Critical, "Not logged in",
//                    "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
//               mBox.exec();
//          }
     //     }
}

void MainWindow::showTabs()
{
    EntryForm *entry = new EntryForm(this);
    mw.tabWidget->addTab(entry,entry->windowTitle());

    alldata = new AllData(this);
    mw.tabWidget->addTab(alldata,alldata->windowTitle());
}

//show the about dialog
void MainWindow::about()
{
    About *a = new About(this);
    a->show();

}

void MainWindow::refreshAllData()
{
    alldata->refreshTable();
}








void MainWindow::login()
{

}
void MainWindow::updateAllData()
{

}

void MainWindow::exportData()
{

}

void MainWindow::help()
{

}



//void MainWindow::about()
//{


//     About about;
//     about.exec();
//}



// 

//QSqlDatabase MainWindow::getConnection()
//{
//     //return connection;
//}


// 
//void MainWindow::showEverything()
//{
//     //remove all the tabs first
//     mw.tabWidget->clear();
//     if (connection.isOpen())
//     {
//          //set the vehicle description
//          QString desc = record.value("description").toString();
//          mw.vehicleLabel->setText(desc);

//          //add the entry tab
//          EntryForm *myEntryForm = new EntryForm(this);
//          mw.tabWidget->addTab(myEntryForm,myEntryForm->windowTitle());
          
//          //add the all data tab
//          everything = new AllData(this);
//          mw.tabWidget->addTab(everything, everything->windowTitle());

//          //add the statistics tab
//          stats = new Statistics(this);
//          mw.tabWidget->addTab(stats,stats->windowTitle());
          
//     }
//     else
//     {
//          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
//          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
//          mBox.exec();
//     }
//}//end showEverything

//QSqlRecord MainWindow::getVehicleRecord()
//{
//     return record;
//}

//DatabaseQuery* MainWindow::getQueries()
//{
//    return queries;
//}



//void MainWindow::help()
//{
//     assistant->showDocs("index.html");
//}

//login dialog box
//bool MainWindow:: login ()
//{
//     bool loginOk = false;
     
//     QSettings settings;
//     //read the config file
//     connection.setHostName(settings.value("config/hostname").toString());
//     connection.setDatabaseName(settings.value("config/dbasename").toString());
//     connection.setPort(settings.value("config/port").toInt());
//     Login mylogin;
//     if (mylogin.exec())
//     {
//          username = mylogin.getUsername();
//          password = mylogin.getPassword();
//          //open the mysql dbase connection
//          if (connection.open(username,password))
//          {
//               loginOk = true;
//               alreadyLoggedIn = true;
//          }
//          else
//          {
//               loginOk = false;
//               QMessageBox::warning(this,"Login Failed!", connection.lastError().text(),QMessageBox::Ok,0,0);
//          }
//     }
//     else
//     {
//          loginOk = false;
//     }
//     return loginOk;
//} //end login
 
//void MainWindow::selectVehicle()
//{
//     //qDebug()<<"select vehicle dialog box goes here";
//     //check and see if the database is open first
//     if (connection.isOpen())
//     {
//          QSettings settings;
//          SelectVehicleDialog choose(this);
//          if (choose.exec())
//          {
//               record = choose.getRecord();
//               settings.setValue("config/vehicle", record.value("id").toInt());
//               showEverything();
//          }
//     }
//     else
//     {
//          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
//          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
          
//          mBox.exec();
//     }
//}//end selectVehicle
// 
//when tabs get clicked on, update the info on that particular tab
//void MainWindow::updateAllData()
//{
//     if (mw.tabWidget->tabText(mw.tabWidget->currentIndex()) == "All Data")
//     {
//          everything->refreshTable();
//     }
//     else if (mw.tabWidget->tabText(mw.tabWidget->currentIndex()) == "Statistics")
//     {
//          stats->refreshTables();
//     }
//} //end updateAllData
// 
//void MainWindow::exportData()
//{
//     //qDebug()<<"export the data for the currently selected vehicle";
//     if (connection.isOpen())
//     {
//          QFileDialog dialog(this, tr("Save As..."));
//          dialog.setFileMode(QFileDialog::AnyFile);
//          dialog.setViewMode(QFileDialog::Detail);
//          dialog.setDirectory(QDir::homePath()+"/");
//          QStringList filename;
//          if (dialog.exec())
//          {
//               filename = dialog.selectedFiles();
//               if (filename[0] != "")
//               {
//                    //qDebug()<<filename[0];
//                    if (QFile::exists(filename[0]))
//                    {
//                         QMessageBox message;
//                         message.setText(tr("File already exists!"));
//                         message.setInformativeText(tr("Overwrite?"));
//                         message.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
//                         message.setDefaultButton(QMessageBox::No);
//                         //int value = message.exec();
//                         if (message.exec() == QMessageBox::Yes)
//                         {
//                              //qDebug()<<"overwrite the file and write out the data";
//                              writeData(filename[0]);
//                         }
//                    }//if file exists
//                    else
//                    {
//                         //qDebug()<<"create file and write out the data";
//                         writeData(filename[0]);
//                    }
//               }
//          }//end dialog executed
//     }
//     else
//     {
//          QMessageBox mBox (QMessageBox::Critical, "Not logged in",
//          "Please login first!  Click file->login.", QMessageBox::Ok, this,Qt::Dialog);
//          mBox.exec();
//     }

//}//end exportData();

//void MainWindow::writeData(QString f)
//{
//     //create file to write to
//     QFile file(f);
//     file.open(QIODevice::WriteOnly|QIODevice::Text);
//     QTextStream out(&file);

//     int vehicleId = record.value("id").toInt();

//     QSqlQuery query(connection);
//     QString q = queries->selectFuelMileage();
//     query.prepare(q);
//     query.bindValue(":vehicleid",vehicleId);
//     if (query.exec())
//     {
//          out<<"\"id\",\"miles\",\"gallons\",\"cost\",\"fillup_date\""<<"\n";
//          while(query.next())
//          {
//               QSqlRecord t = query.record();
//               QString theData = "";
//               for (int i=0;i<t.count();i++)
//               {
//                    theData = theData + "\"" + t.value(i).toString() + "\",";
//               }
//               theData = theData.remove(theData.length()-1,1);
//               //qDebug()<<theData;
//               out<<theData<<"\n";
//          }//loop through resultset
//          file.close();
//          QMessageBox mBox (QMessageBox::Information, "Export Data",
//               "Export is completed!", QMessageBox::Ok, this,Qt::Dialog);
//          mBox.exec();
          
//     }//query was executed
//}//end writeData
