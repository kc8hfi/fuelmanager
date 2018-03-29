#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "ui_configurebase.h"
#include "configurevehicle.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QRadioButton>

class Configure : public QDialog, private Ui_configureBase
{
Q_OBJECT
public:
    Configure();
public slots:
    void switchPage(QListWidgetItem*);
    void selectSqlite();
    void selectMariadb();
private:
    Ui_configureBase base;

    ConfigureVehicle *vehicleui;

    QWidget *dbaseSelection;
    QRadioButton *sqliteButton;
    QRadioButton *mariadbButton;

    QWidget *sqliteWidget;
    QLineEdit *filename;
    QLabel *filenameLabel;
    QLineEdit *location;
    QLabel *locationLabel;
    QPushButton *setLocationButton;


    QWidget *mariadbWidget;
    QLabel *hostnameLabel;
    QLineEdit *hostname;
    QLabel *databaseLabel;
    QLineEdit *database;
    QLabel *portLabel;
    QSpinBox *port;


};

#endif // CONFIGURE_H
