#include "testwidget.h"
#include "ui_testwidget.h"
#include <QDebug>

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);

    qDebug()<<"my parent:"<<this->objectName();
}

TestWidget::~TestWidget()
{
    delete ui;
}
