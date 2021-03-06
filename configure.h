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
    Configure(QWidget *parent=0);
    ~Configure();
    void saveChanges();

public slots:
    void switchPage(QListWidgetItem*);
    void selectSqlite();
    void selectMariadb();
    void selectDirectory();
    void buttonBoxApply();
    void buttonBoxOk();
private:
    void checkSettings();
    void connectToDatabase();
    void createTables();
    Ui_configureBase base;

    ConfigureVehicle *vehicleui;

    QWidget *dbaseSelection;
    QButtonGroup *bgrp;
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
