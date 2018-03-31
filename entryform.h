#ifndef ENTRYFORM_H
#define ENTRYFORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class EntryForm;
}

class EntryForm : public QWidget
{
    Q_OBJECT
public slots:
    void okClicked();
public:
    explicit EntryForm(QWidget *parent = 0);
    ~EntryForm();

private:
    Ui::EntryForm *ui;
    MainWindow *owner;
};

#endif // ENTRYFORM_H
