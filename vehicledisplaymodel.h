#ifndef VEHICLEDISPLAYMODEL_H
#define VEHICLEDISPLAYMODEL_H

#include <QSqlTableModel>

class VehicleDisplayModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit VehicleDisplayModel(QObject *parent=0,QSqlDatabase db=QSqlDatabase());
    Qt::ItemFlags flags(const QModelIndex &index) const;


};

#endif // VEHICLEDISPLAYMODEL_H
