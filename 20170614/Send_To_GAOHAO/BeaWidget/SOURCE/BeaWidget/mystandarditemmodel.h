#ifndef MYSTANDARDITEMMODEL_H
#define MYSTANDARDITEMMODEL_H

#include <QStandardItemModel>

class myStandardItemModel : public QStandardItemModel
{
public:
    myStandardItemModel(QObject *parent=NULL) : QStandardItemModel(parent) { }
    myStandardItemModel(int row, int column, QObject *parent=NULL):QStandardItemModel(row, column, parent) { }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // MYSTANDARDITEMMODEL_H
