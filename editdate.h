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

#ifndef EDITDATE_H
#define EDITDATE_H

#include <QDialog>
#include <QDate>

class QCalendarWidget;
class QDialogButtonBox;

class EditDate : public QDialog
{
     Q_OBJECT
     public:
          EditDate();
          ~EditDate();
          void setDate(QDate d);
          QDate getDate();
          int getChangeme ();
     public slots:
          void accept();
     private:
          QCalendarWidget *editor;
          QDialogButtonBox *buttonBox;
          int changeme;
};

#endif //EDITDATE_H
