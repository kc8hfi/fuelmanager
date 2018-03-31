#include "vehicledisplaymodel.h"

VehicleDisplayModel::VehicleDisplayModel(MainWindow *a)
{
    p = a;
}

Qt::ItemFlags VehicleDisplayModel::flags(const QModelIndex &index) const
{
    //column not to edit...
    Qt::ItemFlags flags = QSqlTableModel::flags(index);
    if (index.column() == 0)
        flags &= ~Qt::ItemIsEditable;
    return flags;
}
