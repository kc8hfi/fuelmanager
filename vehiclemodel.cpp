#include "vehiclemodel.h"
#include <QDebug>

VehicleModel::VehicleModel()
{

}

int VehicleModel::sizeColor()
{
    return theColor.size();
}

void VehicleModel::addColor(QColor c)
{
    theColor.append(c);
}

void VehicleModel::clearColor()
{
    theColor.clear();
}



int VehicleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return theData.size();
}

int VehicleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant VehicleModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row()>= theData.size() || index.row()<0)
        return QVariant();
    if (role==Qt::DisplayRole)
    {
        const auto &v = theData.at(index.row());
        if(index.column() ==0)
            return v.id;
        else if (index.column() == 1)
            return v.description;
    }
    if(role== Qt::BackgroundColorRole)
    {
        QColor c = theColor.at(index.row());
        return c;
    }
    return QVariant();
}

QVariant VehicleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Id");
            case 1:
                return tr("Description");
            default:
                return QVariant();
        }
    }
    if(orientation == Qt::Vertical)
    {
        qDebug()<<"this is where we put the vertical headers,  the row numbers for vehicles";
    }
    return QVariant();
}

bool VehicleModel::insertRow(int position, int rows, const QModelIndex &index,Vehicle v,QColor c)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    theData.append(v);
    theColor.append(c);
    endInsertRows();
    return true;
}

bool VehicleModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    theData.removeAt(position);
    theColor.removeAt(position);
    endRemoveRows();
    return true;
}

bool VehicleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        auto v = theData.value(row);
        if(index.column()==0)
            v.id = value.toInt();
        else if (index.column() ==1 )
        {
            v.description = value.toString();
        }
        else
            return false;
        theData.replace(row,v);
        emit(dataChanged(index,index));
        return true;
    }
    return false;
}

Qt::ItemFlags VehicleModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    //make the first column not editable since its the id
    if(index.column() ==0)
        flag &= ~Qt::ItemIsEditable;
    else
        flag = Qt::ItemIsEditable|Qt::ItemIsEnabled;
    return flag;
}
