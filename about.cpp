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

#include <QDebug>
#include <QDialog>
#include <QFile>
#include "about.h"

//constructor
About::About()
{
     aboutBase.setupUi(this);
     QString programName = "Fuel Manager";
     QString version = QApplication::applicationVersion();

     QString licenseFileName = "COPYING";
     QString path = "/usr/share/doc/fuelmanager-";

     QString info = "";
     QString author = "";
     aboutBase.programName->setText(programName + " " + version);

     //open up the authors file,  copyright info
     QFile authorsFile("authors");
     if (authorsFile.exists())
     {
          //open the authors file
          if(authorsFile.open(QIODevice::ReadOnly))
          {
               QTextStream ts (&authorsFile);
               author = author + ts.readAll();
               author = author + "\n";
          }
          aboutBase.author->setText(author);
     }
     //open up the GPL license file
     QFile license(licenseFileName);
     
     QFile docpathlicense(path+version+"/"+licenseFileName);
     //make sure the file is there
     if (license.exists())  
     {
          //open the gpl license file
          if (license.open(QIODevice::ReadOnly))
          {
               QTextStream ts (&license);
               info += ts.readAll();
          }
          else
          {
               info = "Please see \"http://www.gnu.org/licenses\" for the license to this program.";
          }
     }
     else if (docpathlicense.exists())
     {
          if (docpathlicense.open(QIODevice::ReadOnly))
          {
               QTextStream t(&docpathlicense);
               info = info + t.readAll();
          }
          else
               info = "Please see \"http://www.gnu.org/licenses\" for the license to this program.";
     }
     else
     {
          info = "Please see \"http://www.gnu.org/licenses\" for the license to this program.";
     }
     //put the text into the box
     aboutBase.license->setText(info);
} //end about constructor

//destructor
About::~About()
{
}
