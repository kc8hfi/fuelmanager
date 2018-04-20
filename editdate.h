#ifndef EDITDATE_H
#define EDITDATE_H

#include <QDialog>

namespace Ui {
class EditDate;
}

class EditDate : public QDialog
{
    Q_OBJECT

public:
    explicit EditDate(QWidget *parent = 0);
    ~EditDate();

public slots:
    void okClicked();

private:
    Ui::EditDate *ui;
};

#endif // EDITDATE_H
