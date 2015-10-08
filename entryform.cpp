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

#include <QMessageBox>
#include <QtSql>

#include "entryform.h"

EntryForm::EntryForm(MainWindow *p)
     : QWidget(p)
{
     parent = p;
     entryFormBase.setupUi(this);

     themonths+="January";
     themonths+="February";
     themonths+="March";
     themonths+="April";
     themonths+="May";
     themonths+="June";
     themonths+="July";
     themonths+="August";
     themonths+="September";
     themonths+="October";
     themonths+="November";
     themonths+="December";
     entryFormBase.month->clear();

     //add all the months to the combobox
     entryFormBase.month->addItems(themonths);

     //automatically select the current month
     QDate theDate = QDate::currentDate();
     QString monthName = QDate::longMonthName(theDate.month());
     entryFormBase.month->setCurrentIndex(themonths.indexOf(monthName));

     //add the days to the drop down box
     entryFormBase.day->clear();
     for(int i = 1; i<32;i++)
     {
          thedays += QString::number(i);
     }
     entryFormBase.day->addItems(thedays);
     entryFormBase.day->setCurrentIndex(thedays.indexOf(QString::number(theDate.day())));

     //add the years to the drop down box
     for(int i=theDate.year()-3;i<theDate.year()+3;i++)
     {
          theyears +=QString::number(i);
     }
     entryFormBase.year->addItems(theyears);
     entryFormBase.year->setCurrentIndex(theyears.indexOf(QString::number(theDate.year())));

}//end constructor

//destructor
EntryForm::~EntryForm()
{
}

//ok button handler
void EntryForm::okClicked()
{
     QSqlDatabase c = parent->getConnection();
     QSqlRecord r = parent->getVehicleRecord();
     int vehicleId = r.value("id").toInt();

     bool oktoinsert = true;
     bool numberOk = false;
     QString errormsg = "Please check the following fields:\n";
     if (c.isOpen())
     {
          QSqlQuery query(c);
          query.prepare(parent->getQueries()->insertFuelMileage());
          query.bindValue(":vehicleid",vehicleId);

          //check all the fields to make sure something is in there and that it is numbers 
          if (entryFormBase.miles->text().toDouble(&numberOk))
          {
               query.bindValue(":miles", entryFormBase.miles->text());
          }
          else
          {
               oktoinsert = false;
               errormsg += "Miles\n";
          }
          if (entryFormBase.gallons->text().toDouble(&numberOk))
          {
               query.bindValue(":gallons", entryFormBase.gallons->text());
          }
          else
          {
               oktoinsert = false;
               errormsg += "Gallons\n";
          }
          if (entryFormBase.cost->text().toDouble(&numberOk))
          {
               query.bindValue(":cost", entryFormBase.cost->text());
          }
          else
          {
               oktoinsert = false;
               errormsg += "Cost\n";
          }
          QString thedate = entryFormBase.year->currentText() + "-";
          int monthnumber = themonths.indexOf(entryFormBase.month->currentText())+1;
          QString monthNumberText = "0";
          if (monthnumber <10)
          {
               monthNumberText += QString::number(monthnumber);
          }
          else
          {
               monthNumberText = QString::number(monthnumber);
          }
          QString dayNumberText = "0";
          if (entryFormBase.day->currentText().length() <2)
          {
               dayNumberText += entryFormBase.day->currentText();
          }
          else
               dayNumberText = entryFormBase.day->currentText();

          thedate += monthNumberText + "-";
          thedate += dayNumberText;
          query.bindValue(":fillup_date", thedate);
          //its ok to insert the record.  some good value is in each box
          if (oktoinsert)
          {
               if (query.exec())
               {
                    QString stat = "Miles: " + entryFormBase.miles->text() + " ";
                    stat += "Gallons: " + entryFormBase.gallons->text() + " ";
                    stat += "Cost: " + entryFormBase.cost->text() + " ";
                    stat += "Date: " + entryFormBase.month->currentText() +" ";
                    stat += entryFormBase.day->currentText() + ", ";
                    stat += entryFormBase.year->currentText();
                    //set the messages text to indicate what was inserted
                    entryFormBase.message->setText(stat);
                    //clear all the fields
                    entryFormBase.miles->clear();
                    entryFormBase.gallons->clear();
                    entryFormBase.cost->clear();
                    //put the cursor back up at the top
                    entryFormBase.miles->setFocus();
               }
               else	//connection->lastError().text() doesn't have anything in it...
               {
                    qDebug()<<query.lastError();
                    QString error = "Query failed in entry form.\n";
                    error += "query:\t" + query.lastQuery() + "\n\n";
                    //error += connection->lastError().text();
                    //error += query.lastError();
                    error += "Check and make sure the database is running.\n\n";
                    QMessageBox mBox (QMessageBox::Critical, "Problem!", error, QMessageBox::Ok, this,Qt::Dialog);
                    mBox.exec();
               }
          } //end ok to insert
          else	//something wasn't typed in correctly, give the user an error message telling them what is the problem
          {
               QString error = c.lastError().text();
               QMessageBox mBox (QMessageBox::Critical, "Problem!", errormsg, QMessageBox::Ok, this,Qt::Dialog);
               mBox.exec();
          }
     } //end connection is open
} //end okClicked

//cancel button handler
void EntryForm::cancelClicked()
{
     //clear all the fields
     entryFormBase.miles->clear();
     entryFormBase.gallons->clear();
     entryFormBase.cost->clear();
     //set the date back to the current date
     QDate theDate = QDate::currentDate();
     //set the current month
     QString monthName = QDate::longMonthName(theDate.month());
     entryFormBase.month->setCurrentIndex(themonths.indexOf(monthName));
     //set the current day
     entryFormBase.day->setCurrentIndex(thedays.indexOf(QString::number(theDate.day())));
     //set the current year
     entryFormBase.year->setCurrentIndex(theyears.indexOf(QString::number(theDate.year())));
     //set the focus to the miles text field
     entryFormBase.miles->setFocus();
}//end cancelClicked
