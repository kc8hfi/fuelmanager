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

#include "databaseconfigpage.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QSpinBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>

DatabaseConfigPage::DatabaseConfigPage(MainWindow *p)
     :QWidget(p)
{
     parent = p;

     //create a new groupbox
     QGroupBox *dbaseGroupBox = new QGroupBox(tr("Database Selection"));

     //create some buttons	
     sqliteButton = new QRadioButton(tr("SQLite"));
     mysqlButton = new QRadioButton(tr("MySql"));

     //connect the buttons
     connect(sqliteButton, SIGNAL(clicked()), this, SLOT(selectSqlite()));
     connect(mysqlButton, SIGNAL(clicked()), this, SLOT(selectMysql()));

     //add buttons to a layout
     QHBoxLayout *dbaseGroupBoxLayout = new QHBoxLayout;
     dbaseGroupBoxLayout->addWidget(sqliteButton);
     dbaseGroupBoxLayout->addWidget(mysqlButton);
     dbaseGroupBox->setLayout(dbaseGroupBoxLayout);

     //add the groupbox to a layout
     QHBoxLayout *dbaseLayout = new QHBoxLayout;
     dbaseLayout->addWidget(dbaseGroupBox);

     //add the mysql option widget
     mysqlDbaseConfig = new QWidget;
     QLabel *mysqlHostnameLabel = new QLabel(tr("Hostname:"));
     mysqlHostname = new QLineEdit;
     QLabel *mysqlPortLabel = new QLabel(tr("Port:"));
     port = new QSpinBox;
     port->setMaximum(65535);
     port->setValue(3306);
     QLabel *mysqlDbaseLabel = new QLabel(tr("Database:"));
     mysqlDbase = new QLineEdit;

     QGridLayout *mysqlLayout = new QGridLayout;
     mysqlLayout->addWidget(mysqlHostnameLabel,0,0);
     mysqlLayout->addWidget(mysqlHostname,0,1);
     mysqlLayout->addWidget(mysqlPortLabel,0,2);
     mysqlLayout->addWidget(port,0,3);
     mysqlLayout->addWidget(mysqlDbaseLabel,1,0);
     mysqlLayout->addWidget(mysqlDbase,1,1);
     mysqlDbaseConfig->setLayout(mysqlLayout);
     mysqlDbaseConfig->hide ();


     //add in the sqlite options
     sqliteDbaseConfig = new QWidget;
     QGridLayout *sqliteDbaseConfigLayout = new QGridLayout;
     QLabel *sqliteFilenameLabel = new QLabel(tr("Filename:"));
     dbaseFilename = new QLineEdit;
     dbaseFilename->setReadOnly(true);
     dbaseFilename->setText("fuelmanager.db");
     QLabel *dbaseDirLabel = new QLabel(tr("Location:"));
     dbaseDir = new QLineEdit;
     QPushButton *selectDir = new QPushButton("&Select..");
     connect(selectDir,SIGNAL(clicked()), this, SLOT(selectDir()));
     sqliteDbaseConfigLayout->addWidget(dbaseDirLabel,0,0);
     sqliteDbaseConfigLayout->addWidget(dbaseDir,0,1);
     sqliteDbaseConfigLayout->addWidget(selectDir,0,2);
     sqliteDbaseConfigLayout->addWidget(sqliteFilenameLabel,1,0);
     sqliteDbaseConfigLayout->addWidget(dbaseFilename,1,1);
     sqliteDbaseConfig->setLayout(sqliteDbaseConfigLayout);
     sqliteDbaseConfig->hide(); //hide it

     //set up the apply button
     applyButton = new QPushButton(tr("Apply"));
     connect(applyButton,SIGNAL(clicked()),this, SLOT(applyClicked()));
     QHBoxLayout *buttonsLayout = new QHBoxLayout;
     buttonsLayout->addStretch(1);
     buttonsLayout->addWidget(applyButton);
     applyButton->hide();

     //create a layout for the whole thing
     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(dbaseGroupBox);
     mainLayout->addWidget(mysqlDbaseConfig);
     mainLayout->addWidget(sqliteDbaseConfig);
     mainLayout->addWidget(applyButton);
     mainLayout->addStretch(1);
     //mainLayout->addSpacing(12);

     //read the current settings
     readSettings();

     //set the minimum width
     setMinimumWidth(300);
     //set the layout
     setLayout(mainLayout);

}//end DatabasePage constructor

//sqlite button was clicked
void DatabaseConfigPage::selectSqlite()
{
     //readSettings();
     //hide the mysql configuration and make the sqlite config visible
     if (mysqlDbaseConfig->isVisible())
          mysqlDbaseConfig->hide();
     sqliteDbaseConfig->show();
     if (!applyButton->isVisible())
          applyButton->show();
}

//mysql button was clicked
void DatabaseConfigPage::selectMysql()
{
     //readSettings();
     //hide the sqlite config and make the mysql config visible
     if(sqliteDbaseConfig->isVisible())
          sqliteDbaseConfig->hide();
     mysqlDbaseConfig->show ();
     if (!applyButton->isVisible())
          applyButton->show();
}

//directory location selection for the sqlite dbase
void DatabaseConfigPage::selectDir()
{
     QString dirname = QFileDialog::getExistingDirectory(this, tr("Choose a directory"),
     "",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
     dbaseDir->setText(dirname+"/");
}//end selectDir


//apply button handler
void DatabaseConfigPage::applyClicked()
{
     //qDebug()<<"apply button was clicked, need to write the changes";
     QSettings settings;
     //if the sqlite config is visible, write its settings
     if (sqliteDbaseConfig->isVisible())
     {
          if (dbaseDir->text() != "")
          {
               settings.clear();
               settings.setValue("config/databasetype", "sqlite");
               settings.setValue("config/filename", dbaseFilename->text());
               settings.setValue("config/location", dbaseDir->text());
               settings.setValue("config/connection","sqlitedbase");
               //reset the stuff
               parent->checkSettings();
          }
          else
          {
               QMessageBox msg;
               msg.setText("Select a path for the database first");
               msg.exec();
          }
     }
     //if the mysql config is visible,  write it
     if (mysqlDbaseConfig->isVisible())
     {
          settings.clear();
          settings.setValue("config/databasetype", "mysql");
          settings.setValue("config/hostname", mysqlHostname->text());
          settings.setValue("config/dbasename", mysqlDbase->text());
          settings.setValue("config/port", port->value());
          settings.setValue("config/connection", "mysqldbase");
          parent->checkSettings();
     }
}//end applyClicked

void DatabaseConfigPage::readSettings()
{
     //read the config file and set all the options accordingly
     QSettings settings;
     QString dbase = settings.value("config/databasetype").toString();
     //qDebug()<<"inside readSettings: "<<dbase;
     if (dbase == "sqlite")
     {
          sqliteButton->setChecked(true);
          dbaseFilename->setText(settings.value("config/filename").toString());
          dbaseDir->setText(settings.value("config/location").toString());
          selectSqlite();
          //sqliteDbaseConfig->show();
          //applyButton->show();
     }
     if (dbase == "mysql")
     {
          mysqlButton->setChecked(true);
          mysqlHostname->setText(settings.value("config/hostname").toString());
          mysqlDbase->setText(settings.value("config/dbasename").toString());
          port->setValue(settings.value("config/port").toInt()); 
          selectMysql();
     }
}//end readSettings
