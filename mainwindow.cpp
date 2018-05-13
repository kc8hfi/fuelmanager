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
#include <QIcon>

#include "configure.h"
#include "selectvehicle.h"
#include "entryform.h"
#include "about.h"
#include "alldata.h"
#include "login.h"
#include "statistics.h"

//#include "assistant.h"


#include "mainwindow.h"
#include "editdate.h"


//#include "testwidget.h"

MainWindow::MainWindow(QMainWindow *parent)
     :QMainWindow(parent)
{

    mw.setupUi(this);

    //set up the basic info for qsettings
    QCoreApplication::setOrganizationName("fuelmanager");
    //QCoreApplication::setOrganizationDomain("homelinux.com");
    QCoreApplication::setApplicationName("fuelmanager");

    //set the icon
    //QString filename = "/usr/share/icons/hicolor/scalable/apps/fuelmanager.svg";
    QString filename = ":fuelmanager.svg";

//    QFileInfo iconFilename(filename);
//    if (iconFilename.exists())
//    {
//      QIcon icon(filename);
//      setWindowIcon(icon);
//    }

    //load the icon from the resources file
    QIcon icon(filename);
    setWindowIcon(icon);


    //set the window's desired location
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

    //set up the action and select vehicle buttons
    mw.actionLogin->setEnabled(false);
    mw.actionSelect_Vehicle->setEnabled(false);

    //get the instructions tab
    instructionsTab = mw.tabWidget->widget(0);
    instructionsTab->setWindowTitle("Instructions");
    //remove that tab
    mw.tabWidget->removeTab(0);

    //create the tabs
    entry = new EntryForm();
    alldata = new AllData();
    stats = new Statistics();


    //add all the possible databases
    QSqlDatabase::addDatabase("QMYSQL","mariadb");
    QSqlDatabase::addDatabase("QSQLITE","sqlite");

    //check the settings
    checkSettings();
    setVehicleName();
    updateInterface();
    refreshAllData();





    //assistant = new Assistant;


    mw.actionLogin->setIcon(QIcon::fromTheme("format-join-node"));
    mw.actionExport_Data->setIcon(QIcon::fromTheme("document-export-table"));
    //mw.actionConfigure_Fuel_Manager->setIcon(QIcon::fromTheme("applications-system"));  //big gear
    mw.actionConfigure_Fuel_Manager->setIcon(QIcon::fromTheme("preferences-other"));    //wrench with a gear
    //mw.actionConfigure_Fuel_Manager->setIcon(QIcon::fromTheme("folder"));  //
    mw.actionHelp->setIcon(QIcon::fromTheme("help-contents"));
    mw.actionAbout->setIcon(QIcon::fromTheme("help-about"));


}//end constructor

//destructor
MainWindow::~MainWindow()
{
     //delete queries;
     //because it spawns a qprocess, we gotta kill it
     //delete assistant;
}


//configuration
void MainWindow::configure()
{
    Configure *c = new Configure();
    //c->show();
    int returnVal = c->exec();
    //qDebug()<<"what is the return value:"<<returnVal;
    if (returnVal == 1)
    {
        checkSettings();
    }
} //end configuration

void MainWindow::selectVehicle()
{
    //qDebug()<<"show the select vehicle dialog box";
    SelectVehicle *s = new SelectVehicle();
    //s->show();
    if (s->exec())
    {
        //qDebug()<<"now we refresh all the data since they chose a vehicle";
        setVehicleName();
        updateInterface();
        refreshAllData();
    }
}

void MainWindow::setVehicleName()
{
    QSettings settings;
    if (settings.contains("config/vehicle"))
    {
        int id = settings.value("config/vehicle").toInt();
        QString dbaseType = settings.value("config/databasetype").toString();
        QSqlDatabase db = QSqlDatabase::database(dbaseType);

        if (db.open())
        {
            //qDebug()<<"setvehiclename db is open, and we need to get the desc";
            Query q;
            QString name = q.getVehicleDescription(id);
            mw.vehicleLabel->setText(name);
        }
        else
        {
            qDebug()<<"setvehiclename db is NOT open";
        }
    }
    //mw.vehicleLabel->setText(s);
    //qDebug()<<"set the vehicle label to "<<s;
}

//read the config file
void MainWindow::checkSettings()
{
    QSettings settings;
    if (settings.contains("config/databasetype"))
    {
        mw.actionSelect_Vehicle->setEnabled(true);
        QString dbaseType = settings.value("config/databasetype").toString();
        QSqlDatabase db = QSqlDatabase::database(dbaseType);
        if (dbaseType == "sqlite")
        {
            mw.actionLogin->setEnabled(false);
            //qDebug()<<"very beginning get dbase: "<<db.lastError().text();
            QString location = settings.value("config/location").toString();
            QString filename = settings.value("config/filename").toString();
            db.setDatabaseName(location+"/"+filename);
        }
        else if (dbaseType == "mariadb")
        {
            mw.actionLogin->setEnabled(true);
            db.setHostName(settings.value("config/hostname").toString());
            db.setDatabaseName(settings.value("config/database").toString());
            db.setPort(settings.value("config/port").toInt());
            Login login;
            if (login.exec())
            {
                db.setUserName(login.getUsername());
                db.setPassword(login.getPassword());
                if (!db.open())
                {
                    QMessageBox mBox (QMessageBox::Critical, "Error opening database!",
                    db.lastError().text(), QMessageBox::Ok, this,Qt::Dialog);
                    mBox.exec();
                }
            }
        }
    }//end settings contains a database type
}//end checkSettings

void MainWindow::updateInterface()
{
    //hide all the tabs except for the instructions if they haven't selected a vehicle
    QSettings settings;
    if (!settings.contains("config/vehicle"))
    {
        //only show the instructions tab;
        mw.tabWidget->addTab(instructionsTab,instructionsTab->windowTitle());
    }
    else    //hide the instructions tab
    {
        //get rid of all the tabs first
        for (int i=0;i<mw.tabWidget->count();i++)
        {
            QWidget *t = mw.tabWidget->widget(i);
            mw.tabWidget->removeTab(mw.tabWidget->indexOf(t));
        }
        //add all the tabs
        mw.tabWidget->addTab(entry,entry->windowTitle());
        mw.tabWidget->addTab(alldata,alldata->windowTitle());
        mw.tabWidget->addTab(stats,stats->windowTitle());
    }
}

void MainWindow::refreshAllData()
{
    QSettings settings;
    if(settings.contains("config/vehicle"))
    {
        int id = settings.value("config/vehicle").toInt();
        //refresh the all data table
        alldata->refreshTable(id);
        //refresh the statistics
        stats->refreshAllStats(id);
    }
}

//show the about dialog
void MainWindow::about()
{
    About *a = new About(this);
    a->show();

}

void MainWindow::login()
{

}

//when tabs get clicked on, update the info on that particular tab
void MainWindow::updateAllData()
{
    QSettings settings;
    int id = settings.value("config/vehicle").toInt();
    if(mw.tabWidget->currentIndex() == 1)
    {
        alldata->refreshTable(id);
    }
    if (mw.tabWidget->currentIndex() == 2)
    {
        stats->refreshAllStats(id);
    }
} //end updateAllData



void MainWindow::exportData()
{

}

void MainWindow::help()
{

}




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
 
// 
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
