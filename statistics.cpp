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

#include <QTableWidget>
#include <QVBoxLayout>
#include <QSettings>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "statistics.h"
#include "mymodel.h"

Statistics::Statistics(MainWindow *p)
     : QWidget(p)
{
     statsBase.setupUi(this);
     parent = p;
     columnNames += "Miles";
     columnNames += "Gallons";
     columnNames += "MPG";
     columnNames += "Cost";

     months["01"] = "January";
     months["02"] = "February";
     months["03"] = "March";
     months["04"] = "April";
     months["05"] = "May";
     months["06"] = "June";
     months["07"] = "July";
     months["08"] = "August";
     months["09"] = "September";
     months["10"] = "October";
     months["11"] = "November";
     months["12"] = "December";
     
     //get the colors to alternate the row colors with
//      one = QColor(224,229,233);
//      two = Qt::white;
     
//      one = Qt::lightGray;
//      two = Qt::darkCyan;
     
     one = QColor(224,229,233);
     two = Qt::white;
     

     //get rid of all the tabs
     statsBase.tabWidget->clear();

     //create the lifetime tab
     QWidget *lifetime = new QWidget;
     lifetime->setWindowTitle("Lifetime");

     //create and setup a new table
     lifetimeTable = new QTableWidget;
     lifetimeTable->setColumnCount(columnNames.size());
     lifetimeTable->setHorizontalHeaderLabels(columnNames);

     //creat a new vertical box layout and add the table 
     QVBoxLayout *lifetimeLayout = new QVBoxLayout;
     lifetimeLayout->addWidget(lifetimeTable);
     lifetime->setLayout(lifetimeLayout);

     //add the lifetime tab
     statsBase.tabWidget->addTab(lifetime,lifetime->windowTitle());

     //add the yearly tab
     QWidget *yearly = new QWidget;
     yearly->setWindowTitle("Yearly");
     yearlyTable = new QTableView;
     QVBoxLayout *yearlyLayout = new QVBoxLayout;
     yearlyLayout->addWidget(yearlyTable);
     yearly->setLayout(yearlyLayout);
     statsBase.tabWidget->addTab(yearly,yearly->windowTitle());

     //add the monthly tab
     QWidget *monthly = new QWidget;
     monthly->setWindowTitle("Monthly");
     monthlyTable = new QTableView;
     QVBoxLayout *monthlyLayout = new QVBoxLayout;
     monthlyLayout->addWidget(monthlyTable);
     monthly->setLayout(monthlyLayout);
     statsBase.tabWidget->addTab(monthly,monthly->windowTitle());

     model = new MyModel;

} //end constructor

//destructor
Statistics::~Statistics()
{
     delete model;
}

//lifetime statistics
void Statistics::lifetimeStats ()
{
     QSqlDatabase c = parent->getConnection();

     QSqlRecord r = parent->getVehicleRecord();
     int vehicleId = r.value("id").toInt();

     //get the locale's symbol instead of hard-coding a $
     QString currencySymbol = QLocale().currencySymbol();

     //clear the table first
     lifetimeTable->clear ();
     double miles=0.0,gallons=0.0,mpg = 0.0, cost=0.0;
     QString formattedString;
     QTableWidgetItem *temp;

     QFont lifetimeStatsFont;
     lifetimeStatsFont.setPointSize(16);

     if (c.isOpen())
     {
          QSqlQuery query(c);
          query.prepare("select miles,gallons,cost from fuel_mileage where vehicle_id = :vehicleid");
          query.bindValue(":vehicleid",vehicleId);
          if (query.exec())
          {
               while (query.next())
               {
                    //keep running sums
                    miles = miles + query.value(0).toDouble(); //miles
     // 				qDebug()<<query.value(0);
                    gallons = gallons + query.value(1).toDouble(); //gallons
                    cost = cost + query.value(2).toDouble (); //cost
               }
               if (miles != 0.0)
                    mpg = miles/gallons;
               //set the number of rows
               lifetimeTable->setRowCount(1);
               //set the number of columns
               lifetimeTable->setColumnCount(columnNames.size());
               //set column names
               lifetimeTable->setHorizontalHeaderLabels(columnNames);

               formattedString = QString("%L1").arg(miles,0,'f',2);
               //temp = new QTableWidgetItem(QString::number(miles,'f',2));
               temp = new QTableWidgetItem(formattedString);
               temp->setFlags(Qt::ItemIsEnabled);
               //temp->setFont(lifetimeStatsFont);
               lifetimeTable->setItem(0,0,temp);

               //QString str = QString("%L1").arg(d,0,'f',2);
               //temp = new QTableWidgetItem(str);
               formattedString = QString("%L1").arg(gallons,0,'f',2);
               //temp = new QTableWidgetItem(QString::number(gallons,'f',2));
               temp = new QTableWidgetItem(formattedString);
               temp->setFlags(Qt::ItemIsEnabled);
               //temp->setFont(lifetimeStatsFont);
               lifetimeTable->setItem(0,1,temp);

               formattedString = QString("%L1").arg(mpg,0,'f',2);
               //temp = new QTableWidgetItem(QString::number(mpg,'f',2));
               temp = new QTableWidgetItem(formattedString);
               temp->setFlags(Qt::ItemIsEnabled);
               //temp->setFont(lifetimeStatsFont);
               lifetimeTable->setItem(0,2,temp);

               formattedString = QString(currencySymbol+"%L1").arg(cost,0,'f',2);
               //qDebug()<<formattedString;
               //QString t = "$" + QString::number(cost,'f',2);
               temp = new QTableWidgetItem(formattedString);
               temp->setFlags(Qt::ItemIsEnabled);
               //temp->setFont(lifetimeStatsFont);
               lifetimeTable->setItem(0,3,temp);

               //resize rows and columns
               lifetimeTable->resizeColumnsToContents();
               lifetimeTable->resizeRowsToContents();
          }
     } //connection is open
     else
     {
          //good error message to indicate that the database connection is not open
          QMessageBox mBox (QMessageBox::Critical, "Statistics Problem!", 
               "Connection is not open!  Please login first.", QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
     }
} //end lifetime stats

//stats for each year
void Statistics::yearlyStats()
{
     QSqlDatabase c = parent->getConnection();

     //vehicle id and description is here
     QSqlRecord r = parent->getVehicleRecord();
     model->clearEverything();

     if (c.isOpen())
     {
          QSqlQuery query(c);
          
          QSettings settings;
          //get the database type
          QString databaseType = settings.value("config/databasetype").toString();
          QString q = "";
          
          //mysql query, formatted dates are different for each dbms
          if (databaseType == "mysql")
          {
               q = "select date_format(fillup_date,'%Y') tyear, \
                    sum(miles) Miles,\
                    sum(gallons) Gallons, \
                    sum(cost) Cost \
                    from fuel_mileage \
                    where vehicle_id = :id\
                    and date_format(fillup_date,'%Y') != '0000' \
                    group by tyear\
                    order by tyear\
               ";
          }
          //sqlite query, formatted dates are different
          if (databaseType == "sqlite")
          {
               q = "select strftime(\"%Y\",fillup_date) tyear, \
               sum(miles) Miles, \
               sum(gallons) Gallons,\
               sum(cost) Cost \
               from fuel_mileage \
               where vehicle_id = :id \
               and strftime(\"%Y\",fillup_date) != '0000' \
               group by tyear \
               order by tyear \
               ";
          }
          
          query.prepare(q);
          query.bindValue(":id",r.value("id").toInt());
          if(query.exec())
          {
               //get the column headers and set them
               QSqlRecord rec = query.record();
               int columnPosition=0;
               for(int i=0;i<rec.count();i++)
               {
                    if (rec.fieldName(i) != "tyear")
                    {
                         model->setHeaderData(columnPosition,Qt::Horizontal,rec.fieldName(i));
                         columnPosition++;
                    }
               }
               columnPosition++;
               //add the mpg column
               model->setHeaderData(columnPosition,Qt::Horizontal,"MPG");
               
               int switchRowColor=0;
               QList< QList<QVariant> > everything;
               QList<QVariant> t;
               QList<QColor> colors;
               double total_miles = 0.0;
               double total_gallons = 0.0;
               double total_cost = 0.0;
               double mpg = 0.0;
               while (query.next())
               {
                    //clear out the little list that holds a single row of data
                    t.clear();
                    
                    //the first item is the header for that row
                    model->setHeaderData(switchRowColor,Qt::Vertical,query.value(0));

                    //the rest of the columns now
                    for (int i=1; i<query.record().count(); i++)
                    {
                         QVariant c = query.value(i);
                         //don't format strings, only numbers
                         if (c.type() != QVariant::String)
                         {
                              //if its the cost column, put the currency symbol in front
                              if (query.record().fieldName(i)== "Cost")
                                   c = QLocale::system().currencySymbol() + QLocale::system().toString(c.toDouble(),'f',2);
                              else
                                   c = QLocale::system().toString(c.toDouble(), 'f', 2);
                         }
                         t.append(c);
                    }
                    //calculate the fuel mileage as long as the gallons isn't 0
                    if (query.value(2) != 0.0)
                         mpg = query.value(1).toDouble() / query.value(2).toDouble();
                    t.append(mpg);		//mpg
                    
                    //put the row onto the big list
                    everything.append(t);
                    
                    total_miles += query.value(1).toDouble();
                    total_gallons += query.value(2).toDouble();
                    total_cost += query.value(3).toDouble();
                    
                    //set the row color
                    if (switchRowColor %2 == 0)
                         colors.append(two);
                    else
                         colors.append(one);
                    
                    switchRowColor++;
               }
               //add a blank row
               model->setHeaderData(switchRowColor,Qt::Vertical,"");
               t.clear();
               everything.append(t);
               //set the blank row's color
               if (switchRowColor %2 == 0)
                    colors.append(two);
               else
                    colors.append(one);

               //advance to next row
               switchRowColor++;
               
               //set the totals row color,
               if (switchRowColor %2 == 0)
                    colors.append(two);
               else
                    colors.append(one);
               
               //add another vertical header, since we have totals now
               model->setHeaderData(switchRowColor,Qt::Vertical,"Total");
               mpg = 0.0;
               if (total_gallons != 0.0)
               {
                    mpg = total_miles / total_gallons;
               }
               t.clear();
               t.append(QLocale::system().toString(total_miles, 'f', 2));
               t.append(QLocale::system().toString(total_gallons, 'f', 2));
               t.append(QLocale::system().currencySymbol() + QLocale::system().toString(total_cost,'f',2));
               t.append(QLocale::system().toString(mpg, 'f', 2));
               
               everything.append(t);
               
               //set the stuff 
               model->setModelData(everything,colors);
               
               //sets the table model
               yearlyTable->setModel(model);
               
               //make sure alternating row colors is on
               yearlyTable->setAlternatingRowColors(true);
               
               //resize both rows and columns
               yearlyTable->resizeColumnsToContents();
               yearlyTable->resizeRowsToContents();
          }//query executed
          else
          {
               qDebug()<<query.lastError();
               qDebug()<<q;
          }
     }//connection is open

}//end yearlyStats

void Statistics::monthlyStats()
{
     QSqlDatabase c = parent->getConnection();
     QSqlRecord r = parent->getVehicleRecord();

     //int vehicleId = r.value("id").toInt();

     //clear out the model
     model->clearEverything();
          
     QSettings settings;
     QString dbase = settings.value("config/databasetype").toString();
     QList <QColor> rowcolor;
     QList < QList<QVariant> > everything;
     //make sure the connection is open!

     if (c.isOpen())
     {
          QSqlQuery query(c);
          QString y;
          if (dbase == "sqlite")
          {
               y = "select distinct strftime(\"%Y\",fillup_date) from fuel_mileage \
               where strftime(\"%Y\",fillup_date) != '0000' \
               and vehicle_id = :vehicleid \
               order by fillup_date \
               ";
               query.prepare(y);
          }
          if (dbase == "mysql")
          {
               y = "SELECT distinct(date_format(fillup_date,'%Y')) \
               FROM fuel_mileage where date_format(fillup_date,'%Y') != '0000' \
               and vehicle_id = :vehicleid \
               order by fillup_date \
               ";
               query.prepare(y);
          }
     // 		qDebug()<<y;
          query.bindValue(":vehicleid", r.value("id").toInt() );
          QStringList years;
          if(query.exec())
          {
               int i=0;
               while (query.next())
               {
                    years += query.value(0).toString();
                    //qDebug()<<query.value(0).toString();
                    //set up the column names, which is the years
                    model->setHeaderData(i,Qt::Horizontal,query.value(0).toString());
                    i++;
               }
               
               //set up the row names (vertical), the month names
               i=0;
               QMapIterator<QString,QString> iterator(months);
               while(iterator.hasNext())
               {
                    iterator.next();
                    model->setHeaderData(i,Qt::Vertical,iterator.value());
                    //model->insertRows(i, 1, QModelIndex());
                    i++;
               }
               
               //model->insertRows(int position, int rows, const QModelIndex &parent);
               //model->insertRows(5, 3, QModelIndex());
               
          }
          //start up a new query now
          QString q;
          if (dbase == "mysql")
          {
               q = "select count(miles) fillups, sum(miles) miles,\
               sum(gallons) gallons,sum(cost) cost\
               from fuel_mileage \
               where date_format(fillup_date,'%Y') = :fillup_year \
               and date_format(fillup_date,'%m') = :fillup_month \
               and vehicle_id = :vehicleid \
               ";
          }
          if (dbase == "sqlite")
          {
               q = "select count(miles) fillups, sum(miles) miles,\
               sum(gallons) gallons,sum(cost) cost\
               from fuel_mileage \
               where vehicle_id = :vehicleid\
               and strftime(\"%Y\",fillup_date) = :fillup_year\
               and strftime(\"%m\",fillup_date) = :fillup_month\
               ";
          }
          //qDebug()<<q;
          query.prepare(q);

          QMapIterator<QString,QString> iterator(months);
          QList<QString> monthKeys = months.keys();
          QList< QList<QVariant> > everything;
          QList<QVariant> t;
          QList<QColor> colors;
          int numrows = 0;
          for (int j=0;j<monthKeys.size();j++)
          {
               t.clear();
               for(int i=0;i<years.size();i++)
               {
     // 				qDebug()<<"\t"<<years.at(i);
                    query.bindValue(":vehicleid", r.value("id").toInt() );
                    query.bindValue(":fillup_year", years.at(i) );
                    query.bindValue(":fillup_month",monthKeys.at(j));
     // 				qDebug()<<q<<"\n";
     // 				qDebug()<<query.boundValues();
                    if (query.exec())
                    {
     // 					qDebug()<<"all the records";
                         QSqlRecord record;
                         while(query.next())
                         {
                              record = query.record();
     // 						qDebug()<<record;
                              double mpg = 0.0;
                              if (record.value("gallons").toDouble() != 0.0)
                              {
                                   mpg = record.value("miles").toDouble() / 
                                             record.value("gallons").toDouble();
                              }
                              QString d = "";
                              if (record.value("fillups").toInt() != 0)
                              {
                                   d = "Fillups: " + record.value("fillups").toString() + "\n";
                                   d += "Miles: " + QLocale::system().toString(record.value("miles").toDouble(),'f',2) + "\n";
                                   d += "Gallons: " + QLocale::system().toString(record.value("gallons").toDouble(),'f',2) + "\n";
                                   d += "Cost: " + QLocale::system().currencySymbol();
                                   d += QLocale::system().toString(record.value("cost").toDouble(),'f',2) + "\n";
                                   d += "MPG: " + QLocale::system().toString(mpg,'f',2);
                              }
                              t.append(d);
     // 						qDebug()<<d;
                         }
                    }
                    else
                    {
                         qDebug()<<query.lastError();
                    }
               }//end loop of years
               //add the little list to the big list
               everything.append(t);
               
               //set the row color
               if (numrows%2 == 0)
                    colors.append(two);	//start out with white first
               else
                    colors.append(one);
               numrows++;
               
          }//end loop of months
          //set the model and stuff here
          
          model->setModelData(everything,colors);
          
          //sets the table model
          monthlyTable->setModel(model);
          
          //make sure alternating row colors is on
          monthlyTable->setAlternatingRowColors(true);
          
          //resize both rows and columns
          monthlyTable->resizeColumnsToContents();
          monthlyTable->resizeRowsToContents();
          
     }//end connection is open
}//end monthyStats


//slot to refresh whichever tab was clicked on
void Statistics::refreshTables()
{
     //qDebug()<<"which tab: "<<statsBase.tabWidget->tabText(statsBase.tabWidget->currentIndex());

     if(statsBase.tabWidget->tabText(statsBase.tabWidget->currentIndex()) == "Lifetime")
          lifetimeStats();
     if(statsBase.tabWidget->tabText(statsBase.tabWidget->currentIndex()) == "Yearly")
          yearlyStats();
     if(statsBase.tabWidget->tabText(statsBase.tabWidget->currentIndex()) == "Monthly")
          monthlyStats();
}
