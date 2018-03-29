#include "configure.h"
#include <QDebug>
#include <QFormLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QHBoxLayout>

Configure::Configure()
{
    base.setupUi(this);

    vehicleui = new ConfigureVehicle();
    vehicleui->hide();

    //create the select database widget
    dbaseSelection = new QWidget();
    sqliteButton = new QRadioButton();
    sqliteButton->setText(tr("sqlite"));
    mariadbButton = new QRadioButton();
    mariadbButton->setText(tr("mariadb"));

    QButtonGroup *bgrp = new QButtonGroup();
    bgrp->addButton(sqliteButton);
    bgrp->addButton(mariadbButton);

    QHBoxLayout *horizontal = new QHBoxLayout();
    horizontal->addWidget(sqliteButton);
    horizontal->addWidget(mariadbButton);

    QGroupBox *groupbox = new QGroupBox();
    groupbox->setTitle(tr("Select a database"));
    groupbox->setLayout(horizontal);


    //sqlite
    sqliteWidget = new QWidget();
    filename = new QLineEdit();
    filename->setText(tr("fuelmanager.db"));
    filenameLabel = new QLabel();
    filenameLabel->setText(tr("Filename:"));
    location = new QLineEdit();
    locationLabel = new QLabel();
    locationLabel->setText(tr("Location:"));
    setLocationButton = new QPushButton();
    setLocationButton->setText(tr("Select..."));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(locationLabel,0,0);
    layout->addWidget(location,0,1);
    layout->addWidget(setLocationButton,0,2);

    layout->addWidget(filenameLabel,1,0);
    layout->addWidget(filename,1,1);
    sqliteWidget->setLayout(layout);

    //mariadb/mysql
    mariadbWidget = new QWidget();
    hostnameLabel = new QLabel();
    hostnameLabel->setText(tr("Hostname"));
    hostname = new QLineEdit();
    databaseLabel = new QLabel();
    databaseLabel->setText(tr("Database"));
    database = new QLineEdit();
    portLabel = new QLabel();
    portLabel->setText(tr("Port"));
    port = new QSpinBox();
    port->setMinimum(1024);
    port->setMaximum(65535);
    port->setValue(3306);

    QFormLayout *mariaLayout = new QFormLayout();
    mariaLayout->addRow(tr("Hostname"),hostname);
    mariaLayout->addRow(tr("Database"),database);
    mariaLayout->addRow(tr("Port"),port);
    mariadbWidget->setLayout(mariaLayout);

    QVBoxLayout *vbox =new QVBoxLayout();
    vbox->addWidget(groupbox);
    vbox->addWidget(sqliteWidget);
    vbox->addWidget(mariadbWidget);
    dbaseSelection->setLayout(vbox);

    //hide the database widgets
    sqliteWidget->hide();
    mariadbWidget->hide();

    //add the dbaseSelection
    base.gridLayout->addWidget(dbaseSelection,0,1);


    //add the vehicle add/edit stuff
    base.gridLayout->addWidget(vehicleui,0,1);






    //add a signal to the sqlite radio button
    connect(sqliteButton, SIGNAL(clicked()), this, SLOT(selectSqlite()));
    //add signal to the mariadb radio button
    connect(mariadbButton,SIGNAL(clicked()), this, SLOT(selectMariadb()));
    //add a signal to the list widget on the left
    connect(base.listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(switchPage(QListWidgetItem*)));


    //select the first item
    base.listWidget->setCurrentItem(base.listWidget->item(0));
    switchPage(base.listWidget->item(0));
}

void Configure::selectSqlite()
{
    if(mariadbWidget->isVisible())
        mariadbWidget->hide();
    sqliteWidget->show();
}

void Configure::selectMariadb()
{
    if (sqliteWidget->isVisible())
        sqliteWidget->hide();
    mariadbWidget->show();
}

void Configure::switchPage(QListWidgetItem* current)
{
    qDebug()<<current->text();
    if (current->text() == "Setup Database")
    {
        dbaseSelection->show();
        vehicleui->hide();
    }
    else if (current->text() == "Add/Edit Vehicles")
    {
        dbaseSelection->hide();
        vehicleui->show();
    }

}
