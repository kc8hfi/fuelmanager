/*!
Copyright 2008-2014 Charles Amey

This file is part of Fuel Manager.

Fuel Manager is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fuel Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fuel Manager.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtSql>
#include <QDialog>
#include <QTableView>
#include <QItemSelectionModel>
#include "selectvehicledialog.h"
#include "vehicledisplaymodel.h"
#include "mainwindow.h"

SelectVehicleDialog::SelectVehicleDialog(MainWindow *p)
     : QDialog (p)
{
     parent = p;

     QVBoxLayout *verticalLayout = new QVBoxLayout;
     QLabel * titleLabel = new QLabel(tr("Your vehicles:"));
     verticalLayout->addWidget(titleLabel);
     view = new QTableView;
     view->setSelectionMode(QAbstractItemView::SingleSelection);
     view->setSelectionBehavior(QAbstractItemView::SelectRows);

     verticalLayout->addWidget(view);

     showVehicles();

     connect(view,SIGNAL(clicked(const QModelIndex&)),this,SLOT(clickme()));

     setLayout(verticalLayout);
     setWindowTitle(tr("Choose a vehicle"));

}//end constructor

SelectVehicleDialog::~SelectVehicleDialog()
{
}//end destructor

void SelectVehicleDialog::showVehicles()
{
     model = new VehicleDisplayModel(parent);
     view->setModel(model);
     model->setTable("vehicles");
     //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();
     //qDebug()<<"select: "<<model->lastError();
     //model->removeColumn(0);
     model->setHeaderData(0,Qt::Horizontal, tr("Id"));
     model->setHeaderData(1,Qt::Horizontal, tr("Description"));
     view->resizeColumnsToContents();

}//end showVehicles

void SelectVehicleDialog::clickme()
{
     QItemSelectionModel *selmodel = view->selectionModel();
     QModelIndex current = selmodel->currentIndex();
     QModelIndexList selected = selmodel->selectedIndexes();

     int i = current.row();
     record = model->record(i);
     emit accept();
}

QSqlRecord SelectVehicleDialog::getRecord()
{
     return record;
}