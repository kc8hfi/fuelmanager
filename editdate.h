#ifndef EDITDATE_H
#define EDITDATE_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class EditDate;
}

class EditDate : public QDialog
{
    Q_OBJECT

public:
    explicit EditDate(QWidget *parent = 0);
    ~EditDate();

    //QPushButton *getOkButton();
    QDate selectedDate();
    void setDate(QDate);


    int getChangeme();

public slots:
//    void okClicked();
    void accept();


private:
    Ui::EditDate *ui;
    int changeme;
};

#endif // EDITDATE_H
