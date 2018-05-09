#include "about.h"
#include "ui_about.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QPushButton>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    QString name = "Fuel Manager";
    version = QApplication::applicationVersion();

    ui->programName->setText(name+" - " + version);
    ui->programLocation->setText("https://github.com/kc8hfi/fuelmanager");

    QString author = getAuthor();
    ui->programAuthor->setText(author);

    QString license = getLicense();
    ui->textBrowser->setText(license);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okClicked()));
}

About::~About()
{
    delete ui;
}


QString About::getAuthor()
{
    QString a = "";
//    QFile file1("authors");
//    QFile file2("/usr/share/doc/fuelmanager/authors");
//    if (file1.exists())
//    {
//        if(file1.open(QIODevice::ReadOnly))
//        {
//            QTextStream ts(&file1);
//            a += ts.readAll();
//        }
//    }
//    else if (file2.exists())
//    {
//        if(file2.open(QIODevice::ReadOnly))
//        {
//            QTextStream ts(&file2);
//            a += ts.readAll();
//        }
//    }
//    else
//    {
//        a = "Charles Amey";
//    }
//    return a;

    QFile file(":/authors");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    a = stream.readAll();
    return a;

}

QString About::getLicense()
{
//    QString l = "";
//    QFile file1("COPYING");
//    QFile file2("/usr/share/doc/fuelmanager/COPYING");
//    if (file1.exists())
//    {
//        qDebug()<<"license file1 is there";
//        if(file1.open(QIODevice::ReadOnly))
//        {
//            QTextStream ts(&file1);
//            l += ts.readAll();
//        }
//    }
//    else if (file2.exists())
//    {
//        if(file2.open(QIODevice::ReadOnly))
//        {
//            QTextStream ts(&file2);
//            l += ts.readAll();
//        }
//    }
//    else
//    {
//        l = "Please see \"http://www.gnu.org/licenses\" for the license to this program.";
//    }
//    return l;

    QString a = "";
    QFile file(":/COPYING");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    a = stream.readAll();
    return a;

}

void About::okClicked()
{
    About::close();
}
