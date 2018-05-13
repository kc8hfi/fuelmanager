#include "vehicledisplaymodel.h"
#include <QDebug>

VehicleDisplayModel::VehicleDisplayModel(QObject *parent,QSqlDatabase db)
    :QSqlTableModel(parent,db)
{
}

Qt::ItemFlags VehicleDisplayModel::flags(const QModelIndex &index) const
{
    //let the item look like its selectable

    Qt::ItemFlags flags = QSqlTableModel::flags(index);
    if (index.column() == 1)
    {
        flags &= ~Qt::ItemIsSelectable;
    }
    return flags;
}
