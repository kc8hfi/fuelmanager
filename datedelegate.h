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

#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>

class EditDate;

class DateDelegate : public QStyledItemDelegate
{
    //Q_OBJECT
public:
    DateDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif









//#ifndef DATEDELEGATE_H
//#define DATEDELEGATE_H

//#include <QWidget>
//#include <QStyleOptionViewItem>
//#include <QStyledItemDelegate>


//class EditDate;

//class DateDelegate : public QStyledItemDelegate
//{
//    Q_OBJECT
//public:
//    DateDelegate(QWidget *parent=0);
//    //~DateDelegate();

//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;





//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

//    void setEditorData (QWidget *editor, const QModelIndex &index) const override;
//    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

//private slots:
//    void commitAndCloseEditor();


//};

//#endif // DATEDELEGATE_H
