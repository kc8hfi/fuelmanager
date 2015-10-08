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
#include "datedelegate.h"
#include "editdate.h"

//DateDelegate::DateDelegate(QList< QList<QVariant> > data, QObject *parent)
DateDelegate::DateDelegate(QObject *parent)
     : QItemDelegate(parent)
{
}

DateDelegate::~DateDelegate()
{
}

QWidget *DateDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex & /*index*/ ) const
{
     //qDebug()<<"createEditor function, before setModal";
     //t = new EditDate();
     EditDate *t = new EditDate();
     t->setModal(true);
     return t;
}//end createEditor

void DateDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
     QString value = index.model()->data(index, Qt::DisplayRole).toString();
     QDate thedate = QDate::fromString(value,"MMMM d, yyyy");
     EditDate *d = static_cast<EditDate*>(editor);
     d->setDate(thedate);
     //qDebug()<<"setEditorData:"<<thedate;
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
     //qDebug("inside setModelData");
     if (index.isValid())
     {
          EditDate *d = static_cast<EditDate *>(editor);
          if (d->getChangeme() == 1)
          {
               //qDebug()<<"change the date to this: "<<d->getDate();
               model->setData(index,d->getDate());
          }

     }//end index was valid
}//end setModelData