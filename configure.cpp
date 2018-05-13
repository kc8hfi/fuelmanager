#include "configure.h"
#include <QDebug>
#include <QFormLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QSqlDatabase>
#include "login.h"
#include "mainwindow.h"

Configure::Configure(QWidget *parent) : QDialog(parent)
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

    bgrp = new QButtonGroup();
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
    connect(setLocationButton,SIGNAL(clicked()), this, SLOT(selectDirectory()));

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

    //add a handler for the ok/apply/cancel button
    connect(base.buttonBox->button(QDialogButtonBox::Apply),SIGNAL(clicked()),this,SLOT(buttonBoxApply()));
    connect(base.buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(buttonBoxOk()));

    //select the first item
    base.listWidget->setCurrentItem(base.listWidget->item(0));
    switchPage(base.listWidget->item(0));


    //check the current settings if there are any
    checkSettings();
}

Configure::~Configure()
{
    delete this;
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
    //qDebug()<<current->text();
    if (current->text() == "Setup Database")
    {
        dbaseSelection->show();
        vehicleui->hide();
    }
    else if (current->text() == "Add/Edit Vehicles")
    {
        dbaseSelection->hide();
        vehicleui->show();
        //qDebug()<<"need to refresh the vehicles from the add/edit vehicles";
        vehicleui->refreshTable();
    }

}

void Configure::selectDirectory()
{
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Choose a directory"),
    "",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    location->setText(dirname);
}


void Configure::buttonBoxApply()
{
    //qDebug()<<"apply was clicked";
    saveChanges();

    //qDebug()<<"connect to the database";
    connectToDatabase();

    //qDebug()<<"create tables if necessary";
    createTables();

    //qDebug()<<"refresh the vehicleui table of vehicles if we are connected to dbase";
    vehicleui->refreshTable();
}
void Configure::buttonBoxOk()
{
    //qDebug()<<"ok was clicked";
    saveChanges();
}

void Configure::saveChanges()
{
    QSettings settings;
    //which box is visible?
    if (sqliteButton->isChecked())
    {
        if (location->text()!="" && filename->text()!="")
        {
            settings.clear();
            settings.setValue("config/databasetype", "sqlite");
            settings.setValue("config/location",location->text());
            settings.setValue("config/filename",filename->text());
        }
        else
        {
            //qDebug()<<"show dialog box for whatever field is empty";
            QMessageBox message;
            QString t = "Please fill out the following:\n";
            if (location->text()=="")
                t += "* Location\n";
            if (filename->text()=="")
                t += "* Filename\n";
            message.setText(t);
            message.exec();
        }
        //qDebug()<<"save the sqlite info";
    }
    else if (mariadbButton->isChecked())
    {
        //qDebug()<<"save the mariadb stuff";
        if (hostname->text()!= "" && database->text()!= "")
        {
            settings.clear();
            settings.setValue("config/databasetype","mariadb");
            settings.setValue("config/hostname",hostname->text());
            settings.setValue("config/database",database->text());
            settings.setValue("config/port",port->text());
        }
        else
        {
            QMessageBox message;
            QString t = "Please fill out the following:\n";
            if (hostname->text()=="")
                t += "* Hostname\n";
            if (database->text()=="")
                t += "* Database\n";
            message.setText(t);
            message.exec();
            //qDebug()<<"dialog box for the empty fields";
        }
    }
}

void Configure::checkSettings()
{
    QSettings settings;
    QString databaseType = settings.value("config/databasetype").toString();
    if(databaseType == "sqlite")
    {
        sqliteButton->setChecked(true);
        filename->setText(settings.value("config/filename").toString());
        location->setText(settings.value("config/location").toString());
        sqliteWidget->show();
    }
    else if (databaseType == "mariadb")
    {
        mariadbButton->setChecked(true);
        hostname->setText(settings.value("config/hostname").toString());
        database->setText(settings.value("config/database").toString());
        port->setValue(settings.value("config/port").toInt());
        mariadbWidget->show();

    }
}

void Configure::connectToDatabase()
{
    QSettings settings;
    if (settings.contains("config/databasetype"))
    {
        QString dbaseType = settings.value("config/databasetype").toString();
        if (dbaseType == "sqlite")
        {
            QSqlDatabase db = QSqlDatabase::database(dbaseType);
            db.close();
            QString location = settings.value("config/location").toString();
            QString filename = settings.value("config/filename").toString();
            db.setDatabaseName(location+"/"+filename);
        }
        else if (dbaseType == "mariadb")
        {
            QSqlDatabase db = QSqlDatabase::database(dbaseType,false);
            db.setHostName(settings.value("config/hostname").toString());
            db.setDatabaseName(settings.value("config/database").toString());
            db.setPort(settings.value("config/port").toInt());
            Login login;
            if (login.exec())
            {
                db.setUserName(login.getUsername());
                db.setPassword(login.getPassword());
                if (!db.open())
                {
                    //qDebug()<<"couldn't open the database in configure checksettingss";
                    //qDebug()<<db.lastError().text();
                    QMessageBox mBox (QMessageBox::Critical, "Error opening database!",
                    db.lastError().text(), QMessageBox::Ok, this,Qt::Dialog);
                    mBox.exec();
                }
            }
        }
    }//configuration has a databasetype
}

void Configure::createTables()
{
    Query q;
    q.createVehicleTable();
    q.createMileageTable();
}


//void Configure::connectToDatabase()
//{
//    QSettings settings;
//    QString databaseType = settings.value("config/databasetype").toString();

//    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection",false);
//    if (databaseType == "sqlite")
//    {
//        qDebug()<<"configure driver name: "<<db.driverName();
//        if (db.driverName() == "" || db.driverName()=="QMYSQL")
//        {
//            if (db.driverName() == "QMYSQL")
//            {
//                QString n = db.connectionName();
//                db.close();
//                db = QSqlDatabase();
//                db.removeDatabase(n);
//            }
//            QString location = settings.value("config/location").toString();
//            QString filename = settings.value("config/filename").toString();
//            db = QSqlDatabase::addDatabase("QSQLITE");
//            db.setDatabaseName(location+"/"+filename);
//            db.open();
//        }
//    }
//    else if (databaseType == "mariadb")
//    {
//        if (db.driverName()=="" || db.driverName()=="QSQLITE")
//        {
//            if(db.driverName() == "QSQLITE")
//            {
//                QString n = db.connectionName();
//                db.close();
//                db = QSqlDatabase();
//                db.removeDatabase(n);
//            }
//            db = QSqlDatabase::addDatabase("QMYSQL");
//            db.setHostName(settings.value("config/hostname").toString());
//            db.setDatabaseName(settings.value("config/database").toString());
//            db.setPort(settings.value("config/port").toInt());
//            qDebug()<<"probably go ahead and login...";
//            Login login;
//            if (login.exec())
//            {
//                db.setUserName(login.getUsername());
//                db.setPassword(login.getPassword());
//                if (!db.open())
//                {
//                    qDebug()<<"couldn't open the database in configure checksettingss";
//                    qDebug()<<db.lastError();
//                }
//            }
//        }
//    }
//}//end connectToDatabase
