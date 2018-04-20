#include "editdate.h"
#include "ui_editdate.h"

EditDate::EditDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDate)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(accepted()),this,SLOT(okClicked()));

}

EditDate::~EditDate()
{
    delete ui;
}

void EditDate::okClicked()
{

}
