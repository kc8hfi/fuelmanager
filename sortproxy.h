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

#ifndef SORTPROXY_H
#define SORTPROXY_H

#include <QSortFilterProxyModel>

class QStringList;

class SortProxy : public QSortFilterProxyModel
{
     public:
          SortProxy(QObject *parent = 0);
          ~SortProxy();
          QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
          /*bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole );*/
     protected:
          bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
     private:
          //QStringList *headers;

};

#endif //SORTPROXY_H
