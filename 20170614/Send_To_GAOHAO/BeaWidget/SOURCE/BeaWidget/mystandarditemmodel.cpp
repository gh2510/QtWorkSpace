#include "mystandarditemmodel.h"


QVariant myStandardItemModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if(role == Qt::BackgroundColorRole )
    {
        if(index.row()%2 == 0)
               return QColor(QColor(226, 241, 246));
        else if(index.row()%2 == 1)
               return QColor(QColor(162, 206, 217));
        return QVariant();
    }
    else
    {
        return QStandardItemModel::data(index,role);
    }
}
