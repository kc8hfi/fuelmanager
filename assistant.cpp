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

#include <QByteArray>
#include <QDir>
#include <QLibraryInfo>
#include <QProcess>
#include <QDebug>

#include <QApplication>

#include "assistant.h"

Assistant::Assistant()
     : process(0)
{
}

Assistant::~Assistant()
{
     //need to close qt assistant before qprocess does
     if (process && process->state() == QProcess::Running)
     {
          process->terminate();
          process->waitForFinished(3000);
     }
     delete process;
}

bool Assistant::startAssistant()
{
     if (!process)
          process = new QProcess();
     if (process->state() != QProcess::Running)
     {
          QString a = QLibraryInfo::location(QLibraryInfo::BinariesPath) + QDir::separator();
          a += QLatin1String("assistant");

          //QApplication::setApplicationVersion(APP_VERSION);

//           qDebug()<<"app version: " << QApplication::applicationVersion();
          
          QString path = "/usr/share/doc/fuelmanager-";
          path += QApplication::applicationVersion() + "/fuelmanager.qhc";
//           qDebug()<<"this is where it should be "<<path;
          QFile helpFile(path);
          if (!helpFile.exists())
          {
               path = "documentation/fuelmanager.qhc";
          }
//           qDebug()<<"load this "<<path;
          QStringList args;
          args << QLatin1String("-collectionFile");
          //args << QLatin1String("documentation/fuelmanager.qhc");
          QByteArray ba = path.toLocal8Bit();
          const char *c_str2 = ba.data();
          args << QLatin1String(c_str2);
          args << QLatin1String("-enableRemoteControl");
          
          //the qhc file has to be there first, if not, run "qcollectiongenerator fuelmanager.qhcp -o fuelmanager.qhc" 
          //from the documentation dir
          
          //start the qt assistant now
          process->start(a,args);
          if (!process->waitForStarted())
          {
               qDebug()<<"Install the qt assistant package to view the help";
               return false;
          }
     }
     return true;
}

void Assistant::showDocs(const QString &p)
{
     if (!startAssistant())
          return;
     QByteArray source("SetSource ");

     source.append("qthelp://fuelmanager/doc/");
     process->write(source + p.toLocal8Bit() + '\n');
}
