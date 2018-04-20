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


}

EditDate::~EditDate()
{
    delete ui;
}

void EditDate::okClicked()
{
    qDebug()<<"date ok was clicked";
}
