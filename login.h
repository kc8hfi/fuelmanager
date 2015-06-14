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

#ifndef LOGIN_H
#define LOGIN_H

#include "ui_loginbase.h"

//give the UI some functionality by subclassing the UI from designer

class Login : public QDialog, private Ui_LoginBase
{
     Q_OBJECT
     public:
          Login(QDialog *parent=0);
          ~Login();
          QString getUsername();
          QString getPassword();
     private slots:
          void checkFields();
     private:
          Ui_LoginBase myui;
};

#endif //LOGIN_H
