#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "ui_configurebase.h"

class Configure : public QDialog, private Ui_configureBase
{
Q_OBJECT
public:
    Configure();
public slots:
    void switchPage(QListWidgetItem*);
private:
    Ui_configureBase base;
};

#endif // CONFIGURE_H
