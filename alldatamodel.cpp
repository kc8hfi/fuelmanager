#include "alldatamodel.h"
#include <QDebug>

AllDataModel::AllDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

AllDataModel::AllDataModel(QList<Mileage> theData, QObject *parent)
    : QAbstractTableModel(parent)
    , theData(theData)
{

}

int AllDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return theData.size();
}

int AllDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant AllDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(index.row() >= theData.size() || index.row()<0)
        return QVariant();
    if(role == Qt::DisplayRole)
    {
        const auto &m = theData.at(index.row());
        if (index.column() == 0)
            return m.id;
        else if (index.column() == 1)
            return m.miles;
        else if (index.column() == 2)
            return m.gallons;
        else if(index.column() == 3)
            return m.cost;
        else if (index.column() == 4)
        {
            return m.date.toString("MMMM d, yyyy");
            qDebug()<<m.date;
            return m.date;
        }
    }
    return QVariant();
}

QVariant AllDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case 0:
                return tr("Id");
            case 1:
                return tr("Miles");
            case 2:
                return tr("Gallons");
            case 3:
                return tr("Cost");
            case 4:
                return tr("Date");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool AllDataModel::insertRow(int position, int rows, const QModelIndex &index,Mileage m)
{
    qDebug()<<"inside insertRow";
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows -1);
//    qDebug()<<"afterbegininsertrows";
//    for (int row=0; row< rows; rows++)
//    {
//        //theData.insert(position, {int,double,double,double,QDate()});
//        Mileage m;
//        theData.insert(position,m);
//    }
//    qDebug()<<"after the loop";
    theData.append(m);
    endInsertRows();
    return true;
}

bool AllDataModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(),position,position+rows-1);
    for (int row = 0; row<rows; ++row)
        theData.removeAt(position);
    endRemoveRows();
    return true;
}

bool AllDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        auto m = theData.value(row);
        if(index.column()== 0)
            m.id = value.toInt();
        else if(index.column()==1)
            m.miles = value.toDouble();
        else if(index.column()==2)
            m.gallons = value.toDouble();
        else if(index.column()==3)
            m.cost = value.toDouble();
        else if (index.column()==4)
            m.date = value.toDate();
        else
            return false;
        theData.replace(row,m);
        emit(dataChanged(index,index));
        return true;
    }
    return false;
}


Qt::ItemFlags AllDataModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}








//AllDataModel::AllDataModel(QObject *parent):QAbstractTableModel(parent)
//{

//}

//int AllDataModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent);
//    return theData.size();
////    if (parent.isValid())
////        return 0;
////    else
////        return theData.size();
//}
//int AllDataModel::columnCount(const QModelIndex &parent) const
//{
//    //we're using a struct for right now
//    //there are 5 columns
//    Q_UNUSED(parent);
//    return 6;
////    if (parent.isValid())
////        return 0;
////    else
////        return 5;
//}

//QVariant AllDataModel::data(const QModelIndex &index, int role) const
//{
//    if (index.isValid())
//    {
////        if (role == Qt::DisplayRole)
////        {
//            Mileage m = theData.at(index.row());
//            qDebug()<<m.id;
//            qDebug()<<m.miles;
//            qDebug()<<m.gallons;
//            qDebug()<<m.cost;
//            qDebug()<<m.date;

//            if (index.column()==0)
//                return m.id;
//            else if (index.column()==1)
//                return m.miles;
//            else if (index.column()==2)
//                return m.gallons;
//            else if (index.column()==3)
//                return m.cost;
//            else if (index.column()==4)
//                return m.date;
//            else
//                return QVariant();

////        }//end check role
////        else
////            return QVariant();
//    }//end check index
//    else
//        return QVariant();
//}


//void AllDataModel::clear()
//{
//    theData.clear();
//    colors.clear();
//}

//void AllDataModel::setModelData(Mileage m, QColor c)
//{
//    theData.append(m);
//    colors.append(c);
//}
