#ifndef VEHICLEDISPLAYMODEL_H
#define VEHICLEDISPLAYMODEL_H

#include <QSqlTableModel>
#include "mainwindow.h"

class VehicleDisplayModel : public QSqlTableModel
{
    Q_OBJECT
public:
    VehicleDisplayModel(MainWindow *);
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    MainWindow *p;
};

#endif // VEHICLEDISPLAYMODEL_H
