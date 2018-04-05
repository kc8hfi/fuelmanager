#ifndef ALLDATAMODEL_H
#define ALLDATAMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include <QDate>

struct Mileage
{
    int id;
    QDate date;
    double miles;
    double gallons;
    double cost;
    double mpg;
};




class AllDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AllDataModel(QObject *parent=0);
    AllDataModel(QList<Mileage> theData, QObject *parent=0);

    int sizeColor();
    void addColor(QColor);
    void clearColor();
    int showMessage(QString,QString);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    bool insertRow(int position, int rows, const QModelIndex &index=QModelIndex(),Mileage ={0,QDate(),0,0,0,0});
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;
private:
    QList<Mileage> theData;
    QList<QColor> theColor;


};

//class AllDataModel : public QAbstractTableModel
//{
//public:
//    AllDataModel(QObject *parent=0);


//    //int QAbstractItemModel::rowCount(const QModelIndex &parent = QModelIndex()) const

//    int rowCount(const QModelIndex &parent) const;
//    int columnCount(const QModelIndex &parent) const;
//    QVariant data(const QModelIndex &index, int role) const;

//    void setModelData(Mileage, QColor);
//    void clear();
//private:
//    QList <Mileage> theData;
//    QList <QColor> colors;
//};

#endif // ALLDATAMODEL_H
