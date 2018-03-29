#include "configure.h"
#include <QDebug>

Configure::Configure()
{
    base.setupUi(this);

    //create the select database widget

    //create the vehicle stuff widget


    connect(base.listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(switchPage(QListWidgetItem*)));


    //select the first item
    base.listWidget->setCurrentItem(base.listWidget->item(0));
    switchPage(base.listWidget->item(0));
}

void Configure::switchPage(QListWidgetItem* current)
{
    qDebug()<<current;
}
