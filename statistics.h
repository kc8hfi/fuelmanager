#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>

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

    void lifetimeStats();
    void yearlyStats();

    void refreshAllStats();

private:
    Ui::Statistics *ui;
    QStandardItemModel *lifetimeModel;

    QStandardItemModel *yearlyModel;
};

#endif // STATISTICS_H
