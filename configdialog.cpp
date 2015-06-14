/*!
 * Copyright 2008-2014 Charles Amey
 * 
 * This file is part of Fuel Manager.
 * 
 * Fuel Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Fuel Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Fuel Manager.  If not, see <http://www.gnu.org/licenses/>.
*/


//#include <QtGui>
#include <QSettings>
#include <QDebug>
#include "databaseconfigpage.h"
#include "configdialog.h"
#include "vehicleconfigpage.h"

//constructor
ConfigDialog::ConfigDialog(MainWindow *p)
	: QDialog(p)
{
     parent = p;
     contentsWidget = new QListWidget;
     contentsWidget->setViewMode(QListView::IconMode);
     contentsWidget->setViewMode(QListView::IconMode);
     contentsWidget->setIconSize(QSize(96, 84));
     contentsWidget->setMovement(QListView::Static);
     contentsWidget->setMaximumWidth(128);
     contentsWidget->setSpacing(12);

     pagesWidget = new QStackedWidget;

     vehiclePage = new VehicleConfigPage(parent);

     pagesWidget->addWidget(new DatabaseConfigPage(parent));
     pagesWidget->addWidget(vehiclePage);

     QPushButton *closeButton = new QPushButton(tr("Close"));
     QPushButton *okButton = new QPushButton(tr("Ok"));

     createIcons();
     contentsWidget->setCurrentRow(0);

     connect(closeButton,SIGNAL(clicked()), this, SLOT(close()));
     connect(okButton,SIGNAL(clicked()), this, SLOT(accept()));

     QHBoxLayout *hlayout = new QHBoxLayout;
     hlayout->addWidget(contentsWidget);
     hlayout->addWidget(pagesWidget,1);

     QHBoxLayout *buttonsLayout = new QHBoxLayout;
     buttonsLayout->addStretch(1);
     buttonsLayout->addWidget(okButton);
     buttonsLayout->addWidget(closeButton);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(hlayout);
     mainLayout->addStretch(1);
     mainLayout->addSpacing(12);
     mainLayout->addLayout(buttonsLayout);
     setLayout(mainLayout);

     setWindowTitle(tr("Configuration"));
} //end constructor

//destructor
ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::switchPage(QListWidgetItem* current,QListWidgetItem* previous)
{
//      QMessageBox msg;
//      msg.setText("something was pressed");
//      msg.exec();
     if (!current)
          current = previous;
     pagesWidget->setCurrentIndex(contentsWidget->row(current));
}//end switchPage

//puts all the options on the left side
void ConfigDialog::createIcons()
{
     QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
     configButton->setText(tr("Database"));
     configButton->setTextAlignment(Qt::AlignHCenter);
     configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QListWidgetItem *vehicleSelection = new QListWidgetItem(contentsWidget);
     vehicleSelection->setText(tr("Vehicles"));
     vehicleSelection->setTextAlignment(Qt::AlignHCenter);
     vehicleSelection->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     connect(contentsWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), 
               this, SLOT(switchPage(QListWidgetItem*,QListWidgetItem*) ));

     connect(contentsWidget,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(somethingClicked(QListWidgetItem*)));
}

void ConfigDialog::somethingClicked(QListWidgetItem *item)
{
     //qDebug()<<item->text();
     if (item->text() == "Vehicles")
     {
          vehiclePage->displayVehicles();
     }
}//end somethingClicked

