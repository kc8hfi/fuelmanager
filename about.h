#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class MainWindow;
namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
    QString getAuthor();
    QString getLicense();
public slots:
    void okClicked();
private:
    Ui::About *ui;
    MainWindow *owner;

    QString version;
};

#endif // ABOUT_H
