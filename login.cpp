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

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "login.h"

#include <iostream>
using namespace std;

//constructor
Login::Login(QDialog *p)
     : QDialog (p)
{
     myui.setupUi(this);
}
//destructor
Login::~Login()
{
}

//check the username and password fields to make sure something is in them
void Login::checkFields()
{
     int fields_ok = 1;
     QString errormsg = "Please check the following:\n";
     if (myui.username->text() == "")
     {
          errormsg = errormsg + "username\n";
          fields_ok = 0;
     }
     if (myui.password->text() == "")
     {
          errormsg = errormsg + "password\n";
          fields_ok = 0;
     }
     if (fields_ok == 1)
     {
          //if all the fields have something in them, emit the accept signal
          emit accept ();
     }
     else
     {
          QMessageBox mBox (QMessageBox::Critical, "Problem!", errormsg, QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
     }
} //end checkFields

//return the username
QString Login::getUsername()
{
     return myui.username->text();
}

//return the password
QString Login::getPassword()
{
     return myui.password->text();
}
