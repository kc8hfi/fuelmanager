#include "vehicledisplaymodel.h"

VehicleDisplayModel::VehicleDisplayModel()
{

}

Qt::ItemFlags VehicleDisplayModel::flags(const QModelIndex &index) const
{
    //let the item look like its selectable
    Qt::ItemFlags flags = QSqlTableModel::flags(index);
    if (index.column() == 1)
        flags &= ~Qt::ItemIsSelectable;
    return flags;
}
