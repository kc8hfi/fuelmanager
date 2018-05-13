#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QMap>

class QStandardItemModel;

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = 0);
    ~Statistics();

    void lifetimeStats(int);
    void yearlyStats(int);
    void monthlyStats(int);

    void refreshAllStats(int);

private:
    Ui::Statistics *ui;

    QMap<QString,QString> monthNames;

    QStandardItemModel *lifetimeModel;

    QStandardItemModel *yearlyModel;

    QStandardItemModel *monthlyModel;
};

#endif // STATISTICS_H
