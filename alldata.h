#ifndef ALLDATA_H
#define ALLDATA_H

#include <QWidget>
#include "alldatamodel.h"

namespace Ui {
class AllData;
}

class AllData : public QWidget
{
    Q_OBJECT

public:
    explicit AllData(QWidget *parent = 0);
    ~AllData();

    void refreshTable(int);
    void testData();

public slots:
    void changedItem(const QModelIndex &, const QModelIndex &);
    void saveData();
private:
    Ui::AllData *ui;

    AllDataModel *model;

    QList <Mileage> changedItems;
};

#endif // ALLDATA_H
