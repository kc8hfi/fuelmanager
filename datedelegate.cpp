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


#include <QDate>
#include <QDebug>
#include "datedelegate.h"
#include "editdate.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QRect>


//DateDelegate::DateDelegate(QList< QList<QVariant> > data, QObject *parent)
DateDelegate::DateDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *DateDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option, const QModelIndex &index) const
//QWidget *DateDelegate::createEditor(QDialog *parent,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

     EditDate *edit = new EditDate(parent);

//    QDesktopWidget *d = QApplication::desktop();

//    int screenWidth, width;
//    int screenHeight, height;

//    screenWidth = d->width();
//    screenHeight = d->height();

//    QSize windowSize;

//    windowSize = parent->size();
//    width = windowSize.width();
//    height = windowSize.height();

//    int x,y;
//    x = (screenWidth-width)/2;
//    y = (screenHeight-height)/2;

//    qDebug()<<"width:"<<x<<" height:"<<y;

//    QRect r(100,100,300,300);
//    //edit->setGeometry(r);
//    //edit->move(x,y);

//    edit->resize(800,600);

//     if (parent != NULL)
//     {
//         qDebug()<<"gonna move";
//         edit->move(300,300);
//     }

    edit->setModal(true);
    return edit;
}//end createEditor

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     QString value = index.model()->data(index, Qt::DisplayRole).toString();
     QDate thedate = QDate::fromString(value,"MMMM d, yyyy");
     EditDate *d = qobject_cast<EditDate*>(editor);
     d->setDate(thedate);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
     if (index.isValid())
     {
          EditDate *d = qobject_cast<EditDate *>(editor);
          if (d->getChangeme() == 1)
          {
               qDebug()<<"change the date to this: "<<d->selectedDate();
               model->setData(index,d->selectedDate());
          }

     }//end index was valid
}//end setModelData


//void DateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    qDebug()<<"inside paint";
//}

//QSize DateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    qDebug()<<"inside sizehint";
//}
















//#include "datedelegate.h"
//#include "editdate.h"

//#include <QDebug>
//#include <QDesktopWidget>
//#include <QApplication>
//#include <QSize>
//#include <QRect>
//#include <QCalendarWidget>
//#include <QComboBox>
//#include <QPushButton>


//DateDelegate::DateDelegate(QWidget *parent) :QStyledItemDelegate(parent)
//{

//}

//void DateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{


//}

//QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
////    QDialog *d = new QDialog(parent);
////    d->move(450,450);
////    return d;
////    EditDate *edit = new EditDate();
////    QDesktopWidget *d = QApplication::desktop();

////    int screenWidth, width;
////    int screenHeight, height;

////    screenWidth = d->width();
////    screenHeight = d->height();

////    QSize windowSize;

////    windowSize = parent->size();
////    width = windowSize.width();
////    height = windowSize.height();

////    int x,y;
////    x = (screenWidth-width)/2;
////    y = (screenHeight-height)/2;

////    qDebug()<<"width:"<<x<<" height:"<<y;

//    //QRect r(100,100,300,300);
//    //edit->setGeometry(r);
//    //edit->move(x,y);


////    return edit;

////    qDebug()<<"my parent is: ";
////    qDebug()<<parent;
////    qDebug()<<"something is wrong ";

////    QCalendarWidget *c = new QCalendarWidget();
////    c->resize(300,300);

////    return c;

////    QComboBox* combobox = new QComboBox(parent);
////    combobox->addItems({"Foo", "Bar", "mrjj"});
////    return combobox;

//    //QDialog *d = new QDialog();
//    //d->exec();
//    //return d;

//    EditDate *edit = new EditDate(parent);

//    //QDialogButtonBox *box = edit->getOkButton();
//    //connect(box,SIGNAL(accepted()),this,SLOT(commitAndCloseEditor()));
//    //connect(b,SIGNAL(clicked(bool)),this,&DateDelegate::commitAndCloseEditor);
//    //connect(edit,SIGNAL(accepted()),this,SLOT(commitAndCloseEditor()));

//    QPushButton *b = edit->getOkButton();
//    connect(b,SIGNAL(clicked()),this,SLOT(commitAndCloseEditor()));

//    //connect(edit->getOkButton(),SIGNAL(clicked()),this,SLOT(commitAndCloseEditor()));

//    //edit->getOkButton()->button(QDialogButtonBox::Ok)

//    edit->setModal(true);
//    //edit->show();
//    return edit;


//}

//void DateDelegate::commitAndCloseEditor()
//{
//    EditDate *editor = qobject_cast<EditDate *>(sender());
//    //qDebug()<<editor->selectedDate().toString();

//    emit commitData(editor);
//    emit closeEditor(editor);
//}

//void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    //qDebug()<<"what is this:"<<index.model()->data(index,Qt::DisplayRole);

//    QString s = index.model()->data(index,Qt::DisplayRole).toString();
//    //qDebug()<<s;
//    QDate d = QDate::fromString(s,"MMMM d, yyyy");
//    //qDebug()<<"date object is:"<<d.toString();

//    EditDate *edit = qobject_cast<EditDate *>(editor);
//    edit->setDate(d);
//}

//void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//    //qDebug()<<"setting the model data";

////    if (index.data().canConvert<AllDataModel>())
////    {
//        EditDate *edit = qobject_cast<EditDate *>(editor);
//        model->setData(index,edit->selectedDate());

////    }
//    //qDebug()<<"add this to the model: ";
//    //qDebug()<<edit->selectedDate().toString();

//}

//QSize DateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{

//}







////QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)
////{
////    Q_UNUSED parent;
////    Q_UNUSED option;
////    EditDate *edit = new EditDate();
////    t->setVisible(true);
////    return t;

////}


////void DateDelegate::setEditorData (QWidget *editor, const QModelIndex &index)
////{

////}

////void DateDelegate::setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)
////{

////}
