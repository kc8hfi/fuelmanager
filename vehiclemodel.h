#ifndef VEHICLEMODEL_H
#define VEHICLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>

struct Vehicle
{
    int id;
    QString description;
};

class VehicleModel : public QAbstractTableModel
{
public:
    VehicleModel();

    int sizeColor();
    void addColor(QColor);
    void clearColor();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    bool insertRow(int position, int rows, const QModelIndex &index=QModelIndex(),Vehicle ={0,QString()},QColor=Qt::white);
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;

private:
    QList<Vehicle> theData;
    QList<QColor> theColor;

};

#endif // VEHICLEMODEL_H
