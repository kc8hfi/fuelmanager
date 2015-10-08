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

#include <QtSql>
#include <QMessageBox>
#include "alldata.h"
#include "alldatamodel.h"
#include "sortproxy.h"
#include "datedelegate.h"

//constructor
AllData::AllData(MainWindow *p)
     :QWidget(p)
{
     everything.setupUi(this);
     parent = p;
     model = new AllDataModel;

     connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),this, SLOT(whichIndex(const QModelIndex &, const QModelIndex &)));
     connect(everything.saveChangesButton, SIGNAL(clicked()), this, SLOT(saveToDatabase()));

     everything.saveChangesButton->setEnabled(false);
     everything.dataTable->setSortingEnabled(true);
     //everything.dataTable->setEditTriggers(QAbstractItemView::DoubleClicked);

     changedItems.clear();

     //set the delegate for the date column
     everything.dataTable->setItemDelegateForColumn(1,new DateDelegate());

     //turn off the editable flag??
     //everything.dataTable->setEditTriggers(NULL);
}//end constructor

//destructor
AllData::~AllData()
{
     delete model;
}

//gets called if the tab gets clicked on
void AllData::refreshTable()
{
     //QSqlDatabase c = QSqlDatabase::database(parent->getConnectionName());
     QSqlDatabase c = parent->getConnection();
     QSqlRecord r = parent->getVehicleRecord();
     int vehicleId = r.value("id").toInt();

     //clear out the data structure
     model->clear();
     if (c.isOpen())
     {
          QSqlQuery query(c);
          QString q = parent->getQueries()->selectFuelMileage();
          query.prepare(q);
          query.bindValue(":vehicleid",vehicleId);

          /*  lightGray and darkCyan are the two colors  */
          //define the two colors to alternate between
          //QColor one = Qt::lightGray;
          /*Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow */
          //one = Qt::darkGray;
          //QColor two = Qt::darkCyan;

          //QColor one(224,229,233);
          //stock colors in use right now
          QColor one = Qt::lightGray;
          QColor two = Qt::darkCyan;

          //testing some different colors 
          one = Qt::white;//QColor(224,229,233);
          two = Qt::lightGray;

          if (query.exec())
          {
               //qDebug()<<"query is good"<<q;
               
               //keep track of the old month and year
               int oldmonth = 0;
               int oldyear = 0;
               //handle the first time through the loop different than the rest
               int firsttime = 0;
               //which color are we on this time
               int whichone = 0;
               int count = 0;
               while(query.next())
               {
                    //qDebug()<<query.value(3).toString();
                    //colors for the entire row
                    QList <QColor> rowcolor;
                    //empty the qlist
                    rowcolor.clear();
                    //list of data for the entire row
                    QList<QVariant> t;
                    //empty out the list
                    t.clear();
                    QDate thedate;  //get the date
                    thedate = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");
                    //first time through the loop
                    if (firsttime == 0)
                    {
                         //put the id
                         t.append(query.value(0));	//id
                         rowcolor.append(one);

                         t.append(thedate.toString("MMMM d, yyyy"));	//date
                         rowcolor.append(one);
                         firsttime =1;
                    }
                    //every other time through the loop
                    else 
                    {
                         if (thedate.year() == oldyear && thedate.month() == oldmonth)  //check month and year
                         {
                              //put the id
                              t.append(query.value(0));	//id
                              if (whichone == 0)
                                   rowcolor.append(one);
                              else
                                   rowcolor.append(two);
                              t.append(thedate.toString("MMMM d, yyyy"));	//date
                              //determine which color needs to be added
                              if (whichone == 0)
                                   rowcolor.append(one);
                              else if (whichone == 1)
                                   rowcolor.append(two);
                         }
                         //month and year don't match
                         else
                         {
                              //put the id
                              t.append(query.value(0));	//id
                              if (whichone == 1)
                              {
                                   whichone = 0;
                                   rowcolor.append(one);
                              }
                              else if (whichone == 0)
                                   {
                                        whichone = 1;
                                        rowcolor.append(two);
                                   }
                              if (whichone == 0)
                                   rowcolor.append(one);
                              else
                                   rowcolor.append(two);
                              t.append(thedate.toString("MMMM d, yyyy"));	//date
                              if (whichone == 0)
                                   rowcolor.append(one);
                              else
                                   rowcolor.append(two);
                         }//end years don't match
                    }//end every other time through loop
                    //add the rest of the data items and colors
                    t.append(query.value(1));	//miles
                    if (whichone == 0)
                         rowcolor.append(one);
                    else
                         rowcolor.append(two);
                    t.append(query.value(2));	//gallons
                    if (whichone == 0)
                         rowcolor.append(one);
                    else
                         rowcolor.append(two);
                    t.append(query.value(3));	//cost
                    if (whichone == 0)
                         rowcolor.append(one);
                    else
                         rowcolor.append(two);
                    double mileage = 0.0;   //holds the mileage
                    if (query.value(2) != 0.0)
                    {
                         mileage = (query.value(1).toDouble()) / (query.value(2).toDouble());
                         t.append(mileage);
                         if (whichone == 0)
                              rowcolor.append(one);
                         else
                              rowcolor.append(two);
                    }
                    else
                    {
                         t.append(mileage);
                         if (whichone == 0)
                              rowcolor.append(one);
                         else
                              rowcolor.append(two);
                    }
                    //put the item on the vector now
                    /*	dataItems.prepend(t);
                    colors.prepend(rowcolor);*/
                    //qDebug("right before we add the row to the model");
                    model->setModelData(t,rowcolor);
                    //set the oldmonth and oldyear for next iteration
                    oldmonth = thedate.month();
                    oldyear = thedate.year();
                    count++;
               }//end while
               //add the data to the model if there is data
               /*      if (dataItems.size() > 0)
               {*/
               //model = new CustomModel(dataItems, colors);
               //model->setModelData(dataItems);
               //model->setModelColors(colors);
               //qDebug("end of the while loop\nthe size is:");
               //qDebug()<<model->getSize();
               //qDebug("size of the colors:");
               //qDebug()<<model->getSizeColors();
               //qDebug("right before the sortproxy");
               proxyModel = new SortProxy();
               //qDebug("after the proxy and stuff is done");
               proxyModel->setSourceModel(model);
               //qDebug("proxy set source model");
               proxyModel->setDynamicSortFilter(true);
               //qDebug("after the sort filter");
               //qDebug("\ngotta set the model on the datatable now");
               //http://labs.trolltech.com/page/Projects/Itemview/Modeltest
               
               //this causes segfault
               if (count >0)
               {
                    everything.dataTable->setModel(proxyModel);
               }
               //everything.dataTable->setModel(model);
               //new ModelTest(model, this);
               // 	       qDebug("after the dataTable->setmodel");
               //row colors
               //everything.dataTable->setAlternatingRowColors(true);

               //      }
               //resize the columns, not working like it should
               //everything.dataTable->resizeColumnsToContents();
               //resize it this way, one column at a time......
               QHeaderView *tableView = everything.dataTable->horizontalHeader();
               tableView->resizeSection(1,200);	//date column

               //hide the first column, the id
               everything.dataTable->setColumnHidden(0,true);

               //update the status text
               everything.informationLabel->setText("");
               QString size;
               size.setNum(model->getSize());
               everything.informationLabel->setText(size + " records");
               //qDebug("at the end of the query");
          } //end if query was valid/true
          else
          {
               QString error = "Query failed in all data.\n Possible problem is that table doesn't exist\n";
               error = error + query.lastQuery() + "\n";
               error = error + c.lastError().text();
               QMessageBox mBox (QMessageBox::Critical, "Problem!", error, QMessageBox::Ok, this,Qt::Dialog);
               mBox.exec();
          }
     } //end connection is open
     else
     {
          QMessageBox mBox (QMessageBox::Critical, "All Data Problem!",
          "Connection is not open!  Please login first.", QMessageBox::Ok, this,Qt::Dialog);
          mBox.exec();
     }
}//end refreshTable

void AllData::whichIndex(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
     //enable the save button
     everything.saveChangesButton->setEnabled(true);
     //save the changed item's index
     changedItems.append(topLeft);
}//end whichIndex

void AllData::saveToDatabase()
{
     QSqlDatabase c = parent->getConnection();
     //QSqlRecord r = parent->getRecord();
     //int vehicleId = r.value("id").toInt();

     /*  qDebug("inside alldata,save to database");
     qDebug("first item in changedItems");
     qDebug()<<changedItems.at(0).row();
     QList <QVariant> t = model->getRow(changedItems.at(0).row());  //the whole row
     qDebug("the entire changed row");
     qDebug()<<t;*/
     //qDebug()<<model->data(changedItems.at(0).row());
     //qDebug()<<model->data(changedItems.at(0).row());  //the whole row
     for (int i=0;i<changedItems.size();i++)
     {
          QList <QVariant> t = model->getRow(changedItems.at(i).row());
          QDate thedate = QDate::fromString(t.at(1).toString(),"MMMM d, yyyy");
          QString savedate = thedate.toString("yyyy-MM-dd");
          //make sure connection is open first
          if (c.isOpen())
          {
               QSqlQuery query(c);
               query.prepare(parent->getQueries()->updateFuelMileage());
               query.bindValue(":miles", t.at(2).toString());
               query.bindValue(":gallons",t.at(3).toString());
               query.bindValue(":cost", t.at(4).toString());
               query.bindValue(":fillup_date",savedate);
               query.bindValue(":id",t.at(0).toString());

               if (!query.exec())
               {
                    QString error = "Query failed while updating!\n";
                    error = error + query.lastQuery() + "\n";
                    error = error + c.lastError().text();
                    QMessageBox mBox (QMessageBox::Critical, "Problem!", error, QMessageBox::Ok, this,Qt::Dialog);
                    mBox.exec();
               }
          }//end connection is open
     }//end for
}//end saveToDatabase
