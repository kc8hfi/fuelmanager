#ifndef ALLDATA_H
#define ALLDATA_H

#include <QWidget>

class MainWindow;
class AllDataModel;

namespace Ui {
class AllData;
}

class AllData : public QWidget
{
    Q_OBJECT

public:
    explicit AllData(QWidget *parent = 0);
    ~AllData();

    void refreshTable();

    void testData();
private:
    Ui::AllData *ui;

    AllDataModel *model;
    MainWindow *owner;
};

#endif // ALLDATA_H
