#ifndef ERRORMANAGE_H
#define ERRORMANAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QTableView>
#include "mystandarditemmodel.h"
#include <QBoxLayout>
#include<QDateTime>
#include "commonbutton.h"
#include"adderrordialog.h"
namespace Ui {
class ErrorManage;
}

class ErrorManage : public QWidget
{
    Q_OBJECT
    
public:
    explicit ErrorManage(QWidget *parent = 0);
    ~ErrorManage();
    commonButton *btn_add;
    commonButton *btn_delete;
    commonButton *btn_update;
     commonButton *btn_show;
    
private:
    Ui::ErrorManage *ui;

    void init_table();

public slots:
    void addEntry();
    void editEntry();
    void showEntry();
    void removeEntry();
    void slot_init();

signals:

   // void signal_update();
private:
     myStandardItemModel * switchTableModel;
     QTableView *tableview;

     QHBoxLayout *bottom_layout;
     QVBoxLayout *mainLayout;
};

#endif // ERRORMANAGE_H
