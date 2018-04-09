#include "login.h"
#include "ui_login.h"
#include <QSettings>
#include <QSqlDatabase>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSettings settings;
    ui->hostnameValue->setText(settings.value("config/hostname").toString());
    ui->databaseValue->setText(settings.value("config/database").toString());
    ui->portValue->setText(settings.value("config/port").toString());

}

Login::~Login()
{
    delete ui;
}

QString Login::getUsername()
{
    return ui->usernameEdit->text();
}

QString Login::getPassword()
{
    return ui->passwordEdit->text();
}
