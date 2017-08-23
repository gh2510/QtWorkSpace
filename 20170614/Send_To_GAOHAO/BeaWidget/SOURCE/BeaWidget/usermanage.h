#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include "mystandarditemmodel.h"
namespace Ui {
class UserManage;
}

class UserManage : public QWidget
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();
    void init_table();
    void setViewSize();
private:
    Ui::UserManage *ui;

public slots:
    void addEntry();
    void addEntry( QString name,QString password,QString userlevel);
    void editEntry();
    void removeEntry();
signals:
    void signal_addRecord(QString); //yangmeng 161026 日志实时更新

private:
     myStandardItemModel * userTableModel;
};


#endif // USERMANAGE_H
