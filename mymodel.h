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

#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>

class QColor;

class MyModel : public QAbstractTableModel
{
     public:
          MyModel(QObject *parent=0);
          
          void setModelData(QList < QList<QVariant> > &d, QList< QColor > &c);
          
          int rowCount(const QModelIndex &parent) const;
          int columnCount(const QModelIndex &parent) const;
          QVariant data(const QModelIndex &index, int role) const;
          QVariant headerData(int section, Qt::Orientation orientation, int role) const;
          bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role=Qt::DisplayRole);
          
          //bool insertRows(int position, int rows, const QModelIndex &parent);
          
          void clearEverything();
          QList <QVariant> getHorizontalHeaders();
          QList <QVariant> getVerticalHeaders();

     private:
          QList < QList<QVariant> > dataItems;
          QList <QColor> colors;
          QList <QVariant> horizontalHeaders;
          QList <QVariant> verticalHeaders;
};


#endif //MYMODEL_H