#include "alldatamodel.h"
#include <QDebug>
#include <QMessageBox>


AllDataModel::AllDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

AllDataModel::AllDataModel(QList<Mileage> theData, QObject *parent)
    : QAbstractTableModel(parent)
    , theData(theData)
{

}

void AllDataModel::addColor(QColor c)
{
    theColor.append(c);
}

int AllDataModel::sizeColor()
{
    return theColor.size();
}

void AllDataModel::clearColor()
{
    theColor.clear();
}

int AllDataModel::showMessage(QString from, QString to)
{
    QMessageBox box;
    int returnValue = QMessageBox::No;
    if(QString::compare(from,to,Qt::CaseInsensitive))
    {
        QString message = "Are you really sure you want to replace\n";
        message += from;
        message += "\nwith\n";
        message += to + "?";
        box.setWindowTitle("Are you sure?");
        box.setIcon(QMessageBox::Question);
        box.setText(message);
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        returnValue = box.exec();
    }
    return returnValue;
}

Mileage AllDataModel::getItem(int index)
{
    //if (index >= && index <)
    //if(index.row() >= theData.size() || index.row()<0)
    return theData.at(index);
}

int AllDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return theData.size();
}

int AllDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

//this gets data from the model
QVariant AllDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(index.row() >= theData.size() || index.row()<0)
        return QVariant();
    if(role == Qt::DisplayRole)
    {
        const auto &m = theData.at(index.row());
//        qDebug()<<"alldatamodel data:";
//        qDebug()<<m.id;
//        qDebug()<<m.miles;
//        qDebug()<<m.gallons;
//        qDebug()<<m.cost;
//        qDebug()<<m.date.toString("MMMM d, yyyy");
        //qDebug()<<"index.column:"<<index.column();
        if (index.column() == 0)
            return m.id;
        else if (index.column() == 1)
        {
            //qDebug()<<"date column"<<m.date.toString();
            //return m.miles;
            return m.date.toString("MMMM d, yyyy");
        }
        else if (index.column() == 2)
        {
            //qDebug()<<"miles column"<<m.miles;
            return m.miles;
        }
        else if(index.column() == 3)
            return m.gallons;
        else if (index.column() == 4)
        {
            //return m.cost;
            return QLocale().toCurrencyString(m.cost);
        }
        else if (index.column() == 5)
            return m.mpg;
    }
    if (role == Qt::EditRole)
    {
        const auto &m = theData.at(index.row());
        if (index.column() == 0)
            return m.id;
        else if (index.column() == 1)
        {
//            qDebug()<<"alldatamodel data, the date column";
//            qDebug()<<m.date.toString();
//            return m.date.toString();

            return m.date.toString("MMMM d, yyyy");
        }
        else if (index.column() == 2)
            return m.miles;
        else if(index.column() == 3)
            return m.gallons;
        else if (index.column() == 4)
        {
            //return m.cost;
            return QLocale().toCurrencyString(m.cost);
        }
        else if (index.column() == 5)
            return m.mpg;
    }
    if(role == Qt::BackgroundColorRole)
    {
        QColor c = theColor.at(index.row());
        return c;
    }
    return QVariant();
}

QVariant AllDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case 0:
                return tr("Id");
            case 1:
                return tr("Date");
            case 2:
                return tr("Miles");
            case 3:
                return tr("Gallons");
            case 4:
                return tr("Cost");
            case 5:
                return tr("MPG");
            default:
                return QVariant();
        }
    }
    if(orientation == Qt::Vertical)
    {
        //@here,  this is where we put the vertical headers,  the row numbers.
        //qDebug()<<"headerData section:"<<section;
        return section +1;
    }
    return QVariant();
}

bool AllDataModel::insertRow(int position, int rows, const QModelIndex &index,Mileage m)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows -1);
//    qDebug()<<"afterbegininsertrows";
//    for (int row=0; row< rows; rows++)
//    {
//        //theData.insert(position, {int,double,double,double,QDate()});
//        Mileage m;
//        theData.insert(position,m);
//    }
//    qDebug()<<"after the loop";
    theData.append(m);
    endInsertRows();
    return true;
}

bool AllDataModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(),position,position+rows-1);
    for (int row = 0; row<rows; ++row)
    //for (int row = 0; row<theData.size(); ++row)
        theData.removeAt(position);

    endRemoveRows();
    return true;
}

//changes data in the model
bool AllDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if(index.isValid() && role == Qt::EditRole)
    {
        //qDebug()<<"gotta add something in the alldatamodel";
        int row = index.row();
        auto m = theData.value(row);
        if(index.column()== 0)
            m.id = value.toInt();
        else if(index.column()==1)
        {
            //qDebug()<<"right here, the date column";
            //qDebug()<<value;
            m.date = value.toDate();
            //qDebug()<<"ok, after m.date was assigned, it is: ";
            //qDebug()<<m.date.toString();
        }
        else if(index.column()==2)
        {
            //this part works fine
            //m.miles = value.toDouble();
            int returnVal = showMessage(QString::number(m.miles),value.toString());
            switch (returnVal)
            {
                case QMessageBox::Yes:
                    m.miles = value.toDouble();
                    if (m.gallons !=0)
                        m.mpg = m.miles/m.gallons;
                    else
                        m.mpg = 0;
                break;
            default:
                break;
            };
        }
        else if(index.column()==3)
        {
            //m.gallons = value.toDouble();
            int returnVal = showMessage(QString::number(m.gallons),value.toString());
            switch (returnVal)
            {
                case QMessageBox::Yes:
                    m.gallons = value.toDouble();
                    if (m.gallons !=0)
                        m.mpg = m.miles/m.gallons;
                    else
                        m.mpg = 0;
                break;
            default:
                break;
            };
        }
        else if (index.column()==4)
        {
            //m.cost = value.toDouble();
            int returnVal = showMessage(QString::number(m.cost),value.toString());
            switch (returnVal)
            {
                case QMessageBox::Yes:
                    m.cost = value.toDouble();
                break;
            default:
                break;
            };
        }
        else if (index.column()==5)
            m.mpg = value.toDouble();
        else
            return false;
        theData.replace(row,m);
        emit(dataChanged(index,index));
        return true;
    }
    return false;
}


Qt::ItemFlags AllDataModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if(index.column()==5)
        flag &= ~Qt::ItemIsEditable;
    else
        flag = Qt::ItemIsEditable|Qt::ItemIsEnabled;
    return flag;

}








//AllDataModel::AllDataModel(QObject *parent):QAbstractTableModel(parent)
//{

//}

//int AllDataModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent);
//    return theData.size();
////    if (parent.isValid())
////        return 0;
////    else
////        return theData.size();
//}
//int AllDataModel::columnCount(const QModelIndex &parent) const
//{
//    //we're using a struct for right now
//    //there are 5 columns
//    Q_UNUSED(parent);
//    return 6;
////    if (parent.isValid())
////        return 0;
////    else
////        return 5;
//}

//QVariant AllDataModel::data(const QModelIndex &index, int role) const
//{
//    if (index.isValid())
//    {
////        if (role == Qt::DisplayRole)
////        {
//            Mileage m = theData.at(index.row());
//            qDebug()<<m.id;
//            qDebug()<<m.miles;
//            qDebug()<<m.gallons;
//            qDebug()<<m.cost;
//            qDebug()<<m.date;

//            if (index.column()==0)
//                return m.id;
//            else if (index.column()==1)
//                return m.miles;
//            else if (index.column()==2)
//                return m.gallons;
//            else if (index.column()==3)
//                return m.cost;
//            else if (index.column()==4)
//                return m.date;
//            else
//                return QVariant();

////        }//end check role
////        else
////            return QVariant();
//    }//end check index
//    else
//        return QVariant();
//}


//void AllDataModel::clear()
//{
//    theData.clear();
//    colors.clear();
//}

//void AllDataModel::setModelData(Mileage m, QColor c)
//{
//    theData.append(m);
//    colors.append(c);
//}
