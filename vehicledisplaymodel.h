#ifndef VEHICLEDISPLAYMODEL_H
#define VEHICLEDISPLAYMODEL_H

#include <QSqlTableModel>

class VehicleDisplayModel : public QSqlTableModel
{
    Q_OBJECT
public:
    VehicleDisplayModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;


};

#endif // VEHICLEDISPLAYMODEL_H
