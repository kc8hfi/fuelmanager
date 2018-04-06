#include "entryform.h"
#include "sqlite.h"
#include "ui_entryform.h"
#include <QDebug>
#include <QPushButton>
#include <QDate>
#include <QDoubleValidator>
#include <QMessageBox>

EntryForm::EntryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryForm)
{
    ui->setupUi(this);
    owner = (MainWindow*)parent;

    //only allow doubles into the text fields
    QDoubleValidator* validator = new QDoubleValidator(this);
    ui->milesLineEdit->setValidator(validator);
    ui->gallonsLineEdit->setValidator(validator);
    ui->costLineEdit->setValidator(validator);


    //handlers for the ok and cancel buttons
    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okClicked()));
    //connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(cl)


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

    //double gallons = ui->gallonsLineEdit->text().toDouble();
    //double cost = ui->costLineEdit->text().toDouble();

    QSettings s;
    int vehicleId = s.value("config/vehicle").toInt();
    QString type = s.value("config/databasetype").toString();
    if (type =="sqlite")
    {
//        Sqlite* c = (Sqlite*)owner->getConnection();
//        if (milesok && gallonsok && costok)
//        {
//            if (c->insertFuelMileage(vehicleId,miles,gallons,cost,date))
//            {
//                owner->statusBar()->showMessage(date);

//                //clear the fields
//                ui->milesLineEdit->setText("");
//                ui->gallonsLineEdit->setText("");
//                ui->costLineEdit->setText("");
//                qDebug()<<"refresh the alldata table";
//                owner->refreshAllData();
//            }
//        }
//        else
//        {
//            QMessageBox msg(QMessageBox::Critical,"Missing Data",message,QMessageBox::Ok,this);
//            msg.exec();
//        }
    }
}

