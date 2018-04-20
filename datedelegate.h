#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QWidget>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>


class EditDate;


class DateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QWidget *parent=0);
    //~DateDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;





    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData (QWidget *editor, const QModelIndex &index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private slots:
    void commitAndCloseEditor();

};

#endif // DATEDELEGATE_H
