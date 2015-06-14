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

#ifndef DATABASECONFIGPAGE_H
#define DATABASECONFIGPAGE_H

#include <QtGui>

class MainWindow;

class DatabaseConfigPage : public QWidget
{
     Q_OBJECT
     public:
          DatabaseConfigPage(MainWindow *parent=0);
     public slots:
          void selectSqlite();
          void selectMysql();
          void selectDir();
          void applyClicked();
     private:
          QWidget *mysqlDbaseConfig;
          QLineEdit *mysqlHostname;
          QLineEdit *mysqlDbase;
          QSpinBox *port;
          MainWindow *parent;

          QRadioButton *sqliteButton;
          QRadioButton *mysqlButton;
          
          QWidget *sqliteDbaseConfig;
          QLineEdit *dbaseDir;
          QLineEdit *dbaseFilename;
          QPushButton *applyButton;
          void readSettings();
};

#endif //DATABASECONFIGPAGE_H