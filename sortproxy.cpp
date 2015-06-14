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
#include <QString>
#include <QStringList>
#include "sortproxy.h"

//constructor
SortProxy::SortProxy(QObject *parent)
     : QSortFilterProxyModel(parent)
{
}

//destructor
SortProxy::~SortProxy()
{
}

//returns the header labels
QVariant SortProxy::headerData(int section, Qt::Orientation orientation,int role) const
{
     //just override the horizontal headers with custom text
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
          if (section == 0 )
          {
               QVariant value("Id");
               return value;
          }
          else if (section == 1 )
          {
               QVariant value("Date");
               return value;
          }
          else if (section == 2)
          {
               QVariant value("Miles");
               return value;
          }
          else if (section == 3)
          {
               QVariant value("Gallons");
               return value;
          }
          else if (section == 4)
          {
               QVariant value("Cost");
               return value;
          }
          else if (section == 5)
          {
               QVariant value("MPG");
               return value;
          }
          //else
               //return QAbstractTableModel::headerData(section,orientation,role);
     } //end horizontal headers

     //otherwise, call the headerData from the base class
     return QAbstractItemModel::headerData(section,orientation,role);
}

//overrides the lessThan to work with the model
bool SortProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
     QVariant leftData = sourceModel()->data(left);
     QVariant rightData = sourceModel()->data(right);
     //qDebug()<<left.column();
     //sort by the date
     if (left.column() == 1)
     {
          QDate l;
          QDate r;
          if (!QDate::fromString(leftData.toString(),"MMMM d, yyyy").isValid())
          {
               l = QDate::fromString("10000101","yyyyMMdd");	//january 01, 1000
               //qDebug()<<l;
          }
          else
          {
               l = QDate::fromString(leftData.toString(),"MMMM d, yyyy");
          }
          if (!QDate::fromString(rightData.toString(),"MMMM d, yyyy").isValid())
          {
               r = QDate::fromString("10000101","yyyyMMdd");	//january 01, 1000
               //qDebug()<<r;
          }
          else
          {
               r = QDate::fromString(rightData.toString(),"MMMM d, yyyy");
          }
          //qDebug()<<l;
          return l<r;
     }
     //sort by miles
     else if (left.column() == 2)
     {
          return leftData.toString().toDouble() < rightData.toString().toDouble();
     }
     //sort by gallons
     else if (left.column() == 3)
     {
          return leftData.toString().toDouble() < rightData.toString().toDouble();
     }
     //sort by cost
     else if (left.column() == 4)
     {
          //qDebug("remove the $");
          QString l = leftData.toString();
          l.remove(0,1);
          QString r = rightData.toString();
          r.remove(0,1);
          return l.toDouble() < r.toDouble();
     }
     //sort by mpg
     else if (left.column() == 5)
     {
          return leftData.toString().toDouble() < rightData.toString().toDouble();
     }
     else
          return false;
} //end lessThan

