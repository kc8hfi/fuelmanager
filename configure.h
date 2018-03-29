#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "ui_configurebase.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class Configure : public QDialog, private Ui_configureBase
{
Q_OBJECT
public:
    Configure();
public slots:
    void switchPage(QListWidgetItem*);
private:
    Ui_configureBase base;

    QWidget *sqliteWidget;
    QLineEdit *filename;
    QLabel *filenameLabel;
    QLineEdit *location;
    QLabel *locationLabel;
    QPushButton *setLocationButton;

};

#endif // CONFIGURE_H
