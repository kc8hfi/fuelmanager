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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include "mainwindow.h"

class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QLineEdit;
class QSpinBox;
class QPushButton;

class VehicleConfigPage;

class ConfigDialog : public QDialog
{
     Q_OBJECT
     public:
     ConfigDialog (MainWindow *parent=0);
     ~ConfigDialog ();
     public slots:
          void switchPage(QListWidgetItem*,QListWidgetItem*);
          void somethingClicked(QListWidgetItem *i);

     private:
          void createIcons();
          void saveSettings();
          MainWindow *parent;
          VehicleConfigPage *vehiclePage;
          
          QListWidget *contentsWidget;
          QStackedWidget *pagesWidget;
          QWidget *sqliteDbaseConfig;
          QWidget *mysqlDbaseConfig;
          QLineEdit *dbaseDir;
          QLineEdit *dbaseFilename;
          QLineEdit *mysqlHostname;
          QLineEdit *mysqlDbase;
          QSpinBox *port;
};

#endif //CONFIGDIALOG_H
