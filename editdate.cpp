#include "editdate.h"
#include "ui_editdate.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>

EditDate::EditDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDate)
{
    ui->setupUi(this);

    //connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okClicked()));
//connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okClicked()));

//    connect(b,
//            SIGNAL(clicked()),
//            this,
//            SLOT(okClicked())
//            );
    //connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(ok)

    //connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(okClicked()));


    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
}

EditDate::~EditDate()
{
    delete ui;
}


//QPushButton *EditDate::getOkButton()
//{
//    return ui->buttonBox->button(QDialogButtonBox::Ok);
//}

QDate EditDate::selectedDate()
{
    return ui->calendarWidget->selectedDate();
}

void EditDate::setDate(QDate d)
{
    ui->calendarWidget->setSelectedDate(d);
}

int EditDate::getChangeme()
{
     return changeme;
}


void EditDate::accept()
{
    changeme = 1;
    close();
}


//void EditDate::okClicked()
//{
    //qDebug()<<"ok was clicked to accept the editdate dialog box";
    //emit(accepted());
//}

//void EditDate::okClicked()
//{
//    //qDebug()<<"in the edit date, ok was clicked";
//}
