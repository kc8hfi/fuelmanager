#include "datedelegate.h"
#include "editdate.h"
#include <QStyledItemDelegate>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QSize>
#include <QRect>
#include <QCalendarWidget>

DateDelegate::DateDelegate(QWidget *parent):QStyledItemDelegate(parent)
{

}

void DateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QDialog *d = new QDialog(parent);
//    d->move(450,450);
//    return d;
//    EditDate *edit = new EditDate();
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

    //QRect r(100,100,300,300);
    //edit->setGeometry(r);
    //edit->move(x,y);


//    return edit;
    QCalendarWidget *c = new QCalendarWidget();
    c->resize(300,300);

    return c;

}

void DateDelegate::commitAndCloseEditor()
{

}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

QSize DateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}







//QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    Q_UNUSED parent;
//    Q_UNUSED option;
//    EditDate *edit = new EditDate();
//    t->setVisible(true);
//    return t;

//}


//void DateDelegate::setEditorData (QWidget *editor, const QModelIndex &index)
//{

//}

//void DateDelegate::setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)
//{

//}
