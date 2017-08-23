#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class UserManage;
}

class UserManage : public QWidget
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();

private:
    Ui::UserManage *ui;

public slots:
    void addEntry();
    void addEntry( QString name,QString password,QString userlevel);
    void editEntry();
    void removeEntry();
signals:


private:
     QSqlTableModel * userTableModel;
};


#endif // USERMANAGE_H

