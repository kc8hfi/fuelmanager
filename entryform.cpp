#include "entryform.h"
#include "ui_entryform.h"
#include <QDebug>
#include <QPushButton>
#include <QDate>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QSettings>
//#include <QDateTime>;
#include "query.h"
#include "mainwindow.h"

EntryForm::EntryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryForm)
{
    ui->setupUi(this);

    //only allow doubles into the text fields
    QDoubleValidator* validator = new QDoubleValidator(this);
    ui->milesLineEdit->setValidator(validator);
    ui->gallonsLineEdit->setValidator(validator);
    ui->costLineEdit->setValidator(validator);

    ui->milesLineEdit->setFocus();
    //handlers for the ok and cancel buttons
    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()),this,SLOT(cancelClicked()));

//    //check to see if the database is open
//    QSqlDatabase db = QSqlDatabase::database();
//    if (!db.isOpen())
//    {
//        qDebug()<<"db is NOT OPEN!";
//    }
}

EntryForm::~EntryForm()
{
    delete ui;
}

void EntryForm::okClicked()
{
    QDate d = ui->calendarWidget->selectedDate();
    QString date = d.toString("yyyy-MM-dd");
    bool milesok = false;
    bool gallonsok = false;
    bool costok = false;
    double miles;
    double gallons;
    double cost;
    QString message = "Please check the following fields:\n";
    if (ui->milesLineEdit->text() != "")
    {
        miles = ui->milesLineEdit->text().toDouble();
        milesok = true;
    }
    else
    {
        message += "Miles\n";
    }
    if (ui->gallonsLineEdit->text() != "")
    {
        gallons = ui->gallonsLineEdit->text().toDouble();
        gallonsok = true;
    }
    else
    {
        message += "Gallons\n";
    }
    if (ui->costLineEdit->text() != "")
    {
        cost = ui->costLineEdit->text().toDouble();
        costok =  true;
    }
    else
    {
        message += "Cost\n";
    }
    QSettings s;
    int vehicleId = s.value("config/vehicle").toInt();

    if (milesok && gallonsok && costok)
    {
        Query c;
        c.insertFuelMileage(vehicleId,miles,gallons,cost,date);

        double mpg = 0.0;
        if (gallons != 0.0)
        {
            mpg = miles/gallons;
        }
        QString message = "Date: " + d.toString("MMMM d, yyyy") + " ";
        message += "Miles: " + QString::number(miles) + " ";
        message += "Gallons: " + QString::number(gallons) + " ";
        message += "Cost: " + QString::number(cost) + " ";
        message += "MPG: " + QString::number(mpg) + " ";

        ui->messageLabel->setText(message);

        //clear the fields
        ui->milesLineEdit->clear();
        ui->gallonsLineEdit->clear();
        ui->costLineEdit->clear();
        ui->milesLineEdit->setFocus();


//        qDebug()<<"refresh the alldata table";
//        MainWindow *w = qobject_cast<MainWindow*>(QApplication::activeWindow());
//        w->refreshAllData();

    }
    else
    {
        QString message = "Please fill in the following:\n";
        if (!milesok)
            message += "*miles\n";
        if (!gallonsok)
            message += "*gallons\n";
        if(!costok)
            message += "*cost\n";
        QMessageBox mBox (QMessageBox::Critical, "Error inserting record",
        message, QMessageBox::Ok, this,Qt::Dialog);
        mBox.exec();

    }
}

void EntryForm::cancelClicked()
{
    ui->milesLineEdit->setText("");
    ui->gallonsLineEdit->setText("");
    ui->costLineEdit->setText("");
    ui->calendarWidget->setSelectedDate(QDate::currentDate());

}
