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

#include <QColor>
#include <QDebug>

#include "mymodel.h"

MyModel::MyModel(QObject *parent)
     : QAbstractTableModel(parent)
{
}

void MyModel::setModelData(QList < QList<QVariant> > &d,QList< QColor > &c)
{
     beginResetModel();
     dataItems = d;
     colors = c;
     endResetModel();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
     return dataItems.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
     if (horizontalHeaders.size() == 0)
          return 0;
     else
          return horizontalHeaders.size();
          
//      if (dataItems.size() == 0)
//           return 0;
//      else
//      {
//           QList<QVariant> t = dataItems.at(0);
//           return t.size();
//      }
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
     if (!index.isValid())
          return QVariant();

     if (role == Qt::DisplayRole)
     {
          QList<QVariant> row;
          if (index.row() < dataItems.size())
               row = dataItems.at(index.row());
          QVariant col;
          if (index.column() <row.size())
          {
               QVariant c = row.at(index.column());
               if (c.type() != QVariant::String)
                    c = QString::number(c.toDouble(),'f',2);
               return c;
          }
          else
               return QVariant();
     }
     if (role == Qt::BackgroundColorRole)
     {
          if (index.row()< colors.size())
          {
               return colors.at(index.row());
          }
          else
               return QVariant();
     }
     return QVariant();
}
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
     if (role != Qt::DisplayRole)
          return QVariant();
     else
     {
          if (orientation == Qt::Horizontal)
          {
               if (section < horizontalHeaders.size())
                    return horizontalHeaders.at(section);
          }
          if (orientation == Qt::Vertical)
          {
               if (section < verticalHeaders.size())
                    return verticalHeaders.at(section);
          }
     }
     return QVariant();
}

bool MyModel::setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role)
{
     if (orientation == Qt::Horizontal)
     {
          horizontalHeaders.insert(section,value);
          emit(headerDataChanged(Qt::Horizontal,section,horizontalHeaders.size()));
          return true;
     }
     if (orientation == Qt::Vertical)
     {
          verticalHeaders.insert(section,value);
          emit(headerDataChanged(Qt::Vertical,section,verticalHeaders.size()));
          return true;
     }
     return false;
}

QList <QVariant> MyModel::getVerticalHeaders()
{
     return verticalHeaders;
}

QList <QVariant> MyModel::getHorizontalHeaders()
{
     return horizontalHeaders;
}

void MyModel::clearEverything()
{
     beginRemoveColumns (QModelIndex(),0,horizontalHeaders.size());
     horizontalHeaders.clear();
     endRemoveColumns();     
     
     beginRemoveRows (QModelIndex(),0,verticalHeaders.size());
     verticalHeaders.clear();
     dataItems.clear();
     colors.clear();
     endRemoveRows();     
}