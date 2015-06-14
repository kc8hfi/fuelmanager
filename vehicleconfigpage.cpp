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
#include <QtSql>

#include "mainwindow.h"
#include "vehicleeditmodel.h"
#include "vehicleconfigpage.h"

VehicleConfigPage::VehicleConfigPage(MainWindow *p)
     : QWidget(p)
{
     parent = p;

     verticalLayout = new QVBoxLayout;
     QLabel * titleLabel = new QLabel(tr("Your vehicles:"));
     verticalLayout->addWidget(titleLabel);
     view = new QTableView;
     verticalLayout->addWidget(view);

     QLabel *addVehicleLabel = new QLabel(tr("Add another vehicle"));
     verticalLayout->addWidget(addVehicleLabel);

     QHBoxLayout *horizontalLayout = new QHBoxLayout;
     QLabel *descriptionLabel = new QLabel(tr("Description"));
     description = new QLineEdit;
     horizontalLayout->addWidget(descriptionLabel);
     horizontalLayout->addWidget(description);

     verticalLayout->addLayout(horizontalLayout);

     QSpacerItem *verticalSpacer = new QSpacerItem(20,100,QSizePolicy::Minimum,QSizePolicy::Expanding);

     verticalLayout->addItem(verticalSpacer);

     QPushButton *applyButton = new QPushButton("Apply");
     connect(applyButton,SIGNAL(clicked()),this,SLOT(saveVehicles()));
     verticalLayout->addWidget(applyButton);

     setLayout(verticalLayout);
     
     displayVehicles();
     
}//end vehicleconfigpage constructor

//destructor
VehicleConfigPage::~VehicleConfigPage()
{
}

void VehicleConfigPage::saveVehicles()
{
     if (parent->getConnection().isOpen())
     {
          //save all the edits
          model->submitAll();
          //re-populate the table
          model->select();
          if (description->text() != "")
          {
               QSqlQuery query(parent->getConnection());
               query.prepare(parent->getQueries()->insertVehicle());
               query.bindValue(":description",description->text());
               if (query.exec())
               {
                    //clear the field
                    description->setText("");
                    //refresh the model
                    model->select();
               }
          }//end description wasn't empty
          
     }//end connection is open
}//end saveVehicles

void VehicleConfigPage::displayVehicles()
{
     QSqlDatabase c = parent->getConnection();
     if (c.isOpen())
     {
          model = new VehicleEditModel(parent);
          view->setModel(model);
          model->setTable("vehicles");
          model->setEditStrategy(QSqlTableModel::OnManualSubmit);
          model->select();
          model->setHeaderData(0,Qt::Horizontal, tr("Id"));
          model->setHeaderData(1,Qt::Horizontal, tr("Description"));
          view->resizeColumnsToContents ();
     }
}//end displayVehicles
