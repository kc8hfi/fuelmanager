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
#include <QDate>
#include <QColor>
#include <QMessageBox>
#include <QLocale>

#include "alldatamodel.h"

//constructor
AllDataModel::AllDataModel(QObject *parent)
     : QAbstractTableModel(parent)
{
     dataItems.clear();
     colors.clear();
}

void AllDataModel::clear()
{
     dataItems.clear();
     colors.clear();
}

//destructor
AllDataModel::~AllDataModel()
{
}

int AllDataModel::dateMessage(QString from,QString to)
{
     QMessageBox mBox;
     int ret = QMessageBox::No;
     if(QString::compare(from, to, Qt::CaseInsensitive) != 0)
     {
          QString message = "Are you really sure you want to replace\n";
          message = message + from;
          message = message + "\nwith\n";
          message = message + to + "?"; 
          
          mBox.setWindowTitle("Are you sure?");
          mBox.setIcon(QMessageBox::Question);
          mBox.setText (message);
          mBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
          ret = mBox.exec();
     }
     else
     {
          mBox.setWindowTitle("No date selected");
          mBox.setIcon(QMessageBox::Information);
          
          mBox.setText("You didn't select a date.\nNo changes will be made.");
          mBox.setStandardButtons(QMessageBox::Ok);
          mBox.exec();
          //qDebug()<<"you didn't pick a date";
     }
     return ret;  
}

int AllDataModel::message(QString from,QString to)
{
     QMessageBox mBox;
     int ret = QMessageBox::No;
     if(QString::compare(from, to, Qt::CaseInsensitive) != 0)
     {
          QString message = "Are you really sure you want to replace\n";
          message = message + from;
          message = message + "\nwith\n";
          message = message + to + "?"; 
          
          mBox.setWindowTitle("Are you sure?");
          mBox.setIcon(QMessageBox::Question);
          mBox.setText (message);
          mBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
          ret = mBox.exec();
     }
     return ret;  
}


void AllDataModel::setModelData (QList < QVariant > d, QList< QColor > c)
{
     dataItems.append(d);
     colors.append(c);
}

int AllDataModel::getSize()
{
     return dataItems.size();
}

int AllDataModel::getSizeColors()
{
     return colors.size();
}

QList <QVariant> AllDataModel::getRow (int rowIndex)
{
     return dataItems.at(rowIndex);  //the whole row
}

//gets the data from the model
QVariant AllDataModel::data(const QModelIndex &index,int role) const
{
     if (index.isValid())
     {
          if (role == Qt::DisplayRole)
          {
               QList <QVariant> t = dataItems.at(index.row());
               QVariant u = t.at(index.column());
               if (index.column() == 4)
               {
                    //QString m = QLocale().toString(u.toDouble(),'f',2);
                    QString c = QLocale().toCurrencyString(u.toDouble());
                    
//                     QString c = "$";
//                     QString m;
//                     m.setNum(u.toDouble(), 'f',2);
//                     c = c + m;
                    return c;
               }
               if (index.column() == 5)
               {
                    double mpg = u.toDouble();
                    QString m;
                    m.setNum(mpg, 'f',3);
                    return m;
               }
               return u.toString();
          }
          if (role == Qt::BackgroundColorRole)
          {
               QList <QColor> row = colors.at(index.row());
               QColor c = row.at(index.column());
               return c;
          }
          if (role == Qt::EditRole)
          {
               QList <QVariant> t = dataItems.at(index.row());
               QVariant u = t.at(index.column());
               return u;
          }
     }
     return QVariant();
}//end data

//returns the number of rows in the model
int AllDataModel::rowCount(const QModelIndex &index) const
{
     if (index.isValid())
          return 0;
     return dataItems.size();
}

//returns the number of columns in the model
int AllDataModel::columnCount(const QModelIndex &index) const
{
     if (index.isValid())
          return 0;
     QList <QVariant> t = dataItems.at(0);
     return t.size();
}

Qt::ItemFlags AllDataModel::flags(const QModelIndex &index) const
{
     if (!index.isValid())
          return Qt::ItemIsEnabled;
     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool AllDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     if (index.isValid() && role == Qt::EditRole)
     {
          //date column
          if (index.column() == 1)
          {
               QList <QVariant> t = dataItems.at(index.row());  //the whole row
               QVariant u = t.at(index.column());
               QString from = u.toString();
               QString to = value.toDate().toString("MMMM d, yyyy");
               int ret = dateMessage(from,to);
               switch(ret)
               {
                    case QMessageBox::Yes:
                         t.replace(index.column(),to);	//entire row
                         dataItems.replace(index.row(),t);	//entire column now
                         emit dataChanged(index,index);
     /*
     No, no, no, don't do it this way,
     more like this instead
     [23:03] <ahigerd1> There's a "dirty" property and a dataChanged signal for that :P
     [23:04] <kc8hfi> oh, I see.  So the setModelData of the delegate could emit the dataChanged signal, and I could have that 
                    button's slot hooked to it?
     [23:04] <ahigerd1> The model itself emits it for you
     [23:04] <ahigerd1> QAbstractItemModel::dataChanged(QModelIndex, QModelIndex)
     [23:04] <ahigerd1> Connect to setEnabled()

     */
     //emit model->dataChanged(index,index);
                    
                         return true;
                    break;
                    default:
                    break;
               };
          }//column was 1
          //miles column
          if (index.column() == 2)
          {
               QList <QVariant> t = dataItems.at(index.row());  //the whole row
               QVariant u = t.at(index.column());
               QString from = u.toString();
               QString to = value.toString();
               int ret = message(from,to);
               switch(ret)
               {
               case QMessageBox::Yes:
                    t.replace(index.column(),to);	//entire row
                    //recalculate the fuel mileage
                    t.replace(index.column()+3, to.toDouble()/t.at(index.column() + 1).toDouble());
                    dataItems.replace(index.row(),t);	//entire column now
                    emit dataChanged(index,index);
                    return true;
               break;
               default:
               break;
               };
          }
          //gallons column
          if (index.column() == 3)
          {
               QList <QVariant> t = dataItems.at(index.row());  //the whole row
               QVariant u = t.at(index.column());
               QString from = u.toString();
               QString to = value.toString();
               int ret = message(from,to);
               switch(ret)
               {
               case QMessageBox::Yes:
               t.replace(index.column(),to);	//entire row
               //recalculate the fuel mileage
               if (to.toDouble() != 0.0)
               {
                    t.replace(index.column()+2,t.at(index.column() - 1).toDouble()/to.toDouble());
               }
               dataItems.replace(index.row(),t);	//entire column now
               emit dataChanged(index,index);
               return true;
               break;
               default:
               break;
               };
          }
          //cost column
          if (index.column() == 4)
          {
               QList <QVariant> t = dataItems.at(index.row());  //the whole row
               QVariant u = t.at(index.column());
               QString from = u.toString();
               QString to = value.toString();
               int ret = message(from,to);
               switch(ret)
               {
               case QMessageBox::Yes:
               t.replace(index.column(),to);	//entire row
               dataItems.replace(index.row(),t);	//entire column now
               emit dataChanged(index,index);
               return true;
               break;
               default:
               break;
               };
          }
     }
     return false;
}//end setData

// bool AllDataModel::insertRows(int position, int rows, const QModelIndex &index)
// {
//   qDebug("insert rows");
//   return true;
// }
// 
// bool AllDataModel::removeRows(int position, int rows, const QModelIndex &index)
// {
//   qDebug("removeRows");
//   return true;
// }


