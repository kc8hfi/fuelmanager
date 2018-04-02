#include "alldatamodel.h"
#include <QDebug>
AllDataModel::AllDataModel(QObject *parent):QAbstractTableModel(parent)
{

}

int AllDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return theData.size();
//    if (parent.isValid())
//        return 0;
//    else
//        return theData.size();
}
int AllDataModel::columnCount(const QModelIndex &parent) const
{
    //we're using a struct for right now
    //there are 5 columns
    Q_UNUSED(parent);
    return 6;
//    if (parent.isValid())
//        return 0;
//    else
//        return 5;
}

QVariant AllDataModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
//        if (role == Qt::DisplayRole)
//        {
            Mileage m = theData.at(index.row());
            qDebug()<<m.id;
            qDebug()<<m.miles;
            qDebug()<<m.gallons;
            qDebug()<<m.cost;
            qDebug()<<m.date;

            if (index.column()==0)
                return m.id;
            else if (index.column()==1)
                return m.miles;
            else if (index.column()==2)
                return m.gallons;
            else if (index.column()==3)
                return m.cost;
            else if (index.column()==4)
                return m.date;
            else
                return QVariant();

//        }//end check role
//        else
//            return QVariant();
    }//end check index
    else
        return QVariant();
}


void AllDataModel::clear()
{
    theData.clear();
    colors.clear();
}

void AllDataModel::setModelData(Mileage m, QColor c)
{
    theData.append(m);
    colors.append(c);
}
