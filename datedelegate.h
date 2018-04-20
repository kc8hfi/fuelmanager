#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QWidget>
#include <QStyleOptionViewItem>


clas EditDate;

class DateDelegate : public QItemDelegate
{
public:
    DateDelegate();
    ~DateDelegate();

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData (QWidget *editor, const QModelIndex &index) const;
    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    EditDate *edit;

};

#endif // DATEDELEGATE_H
