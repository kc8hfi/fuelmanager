/**
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
 */


#ifndef ENTRYFORM_H
#define ENTRYFORM_H

#include <QStringList>
#include "ui_entryform.h"
#include "mainwindow.h"

class QSqlDatabase;

//entry form widget
class EntryForm : public QWidget, private Ui_EntryFormBase
{
     Q_OBJECT
     public:
          EntryForm (MainWindow *p);
          ~EntryForm();
     public slots:
          void okClicked ();
          void cancelClicked();
     private:
          Ui_EntryFormBase entryFormBase;
          MainWindow *parent;
          QStringList themonths;
          QStringList thedays;
          QStringList theyears;
};

#endif //ENTRYFORM_H
