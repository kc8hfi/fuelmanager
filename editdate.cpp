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

#include <QMessageBox>
#include <QDebug>
#include <QCalendarWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "editdate.h"


EditDate::EditDate()
{
/*     e.setupUi(this);
     QMessageBox mBox (QMessageBox::Critical, "Problem!", error, QMessageBox::Ok, this,Qt::Dialog);
     mBox.exec();*/
     //qDebug()<<"inside the editdate constructor\n";
     buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
          | QDialogButtonBox::Cancel);

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
     
     editor = new QCalendarWidget();
     //editor->setSelectionMode(QCalendarWidget::SingleSelection);
     editor->setGridVisible(true);
     editor->setMinimumSize(300,300);     
     
     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(editor);
     mainLayout->addWidget(buttonBox);
     
     setLayout(mainLayout);
     changeme = 0;
}//end constructor

EditDate::~EditDate()
{
     delete editor;
     delete buttonBox;
}

void EditDate::setDate(QDate thedate)
{
     //qDebug()<<"before setting the date:"<<thedate;
     editor->setSelectedDate(thedate);
}

QDate EditDate::getDate()
{
     //qDebug()<<"getDate: "<<editor->selectedDate();
     return editor->selectedDate();
}

int EditDate::getChangeme()
{
     return changeme;
}

void EditDate::accept ()
{
     //qDebug()<<"accept the changes\n";
     //qDebug()<<editor->selectedDate();
     changeme = 1;
     close();
}//end accept

