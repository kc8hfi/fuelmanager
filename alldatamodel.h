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

#ifndef ALLDATAMODEL_H
#define ALLDATAMODEL_H

#include <QAbstractTableModel>

class QColor;

class AllDataModel : public QAbstractTableModel
{
     Q_OBJECT
     public:
          //AllDataModel(QList< QList<QVariant> > data, QList< QList<QColor> > color,QObject *parent=0);
          AllDataModel (QObject *parent=0);
          ~AllDataModel();
          
          int rowCount(const QModelIndex &parent=QModelIndex()) const;
          int columnCount(const QModelIndex &parent=QModelIndex()) const;
          
          QVariant data(const QModelIndex &item,int role=Qt::DisplayRole) const;
          Qt::ItemFlags flags(const QModelIndex &index) const;

          bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
          
          //QVariant headerData(int section, Qt::Orientation orientation,int role) const;
          //bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole );
          
//           bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
//           bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

          //bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
          //bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
          void setModelData (QList < QVariant > d, QList< QColor > c);
          QList <QVariant> getRow (int rowIndex);
          int getSize();
          int getSizeColors();
          void clear();
     //signals:
          //void somethingChanged(bool);
          //void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight );
     private:
          int dateMessage(QString from,QString to);
          int message(QString from,QString to);
          QList < QList<QVariant> > dataItems;
          QList < QList<QColor> > colors;
          
};
#endif //ALLDATAMODEL_H
