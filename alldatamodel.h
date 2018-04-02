#ifndef ALLDATAMODEL_H
#define ALLDATAMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include <QDate>

struct Mileage
{
    int id;
    double miles;
    double gallons;
    double cost;
    QDate date;
};

class AllDataModel : public QAbstractTableModel
{
public:
    AllDataModel(QObject *parent=0);


    //int QAbstractItemModel::rowCount(const QModelIndex &parent = QModelIndex()) const

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void setModelData(Mileage, QColor);
    void clear();
private:
    QList <Mileage> theData;
    QList <QColor> colors;
};

#endif // ALLDATAMODEL_H
