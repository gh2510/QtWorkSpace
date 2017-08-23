#ifndef SWITCHMANAGE_H
#define SWITCHMANAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QBoxLayout>
#include "commonbutton.h"
#include "mystandarditemmodel.h"

namespace Ui {
class SwitchManage;
}

class SwitchManage : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchManage(QWidget *parent = 0);
    ~SwitchManage();
    commonButton *btn_add;
    commonButton *btn_delete;
    commonButton *btn_update;

private:
    Ui::SwitchManage *ui;
    void init_table();

public slots:
    void addEntry();
    void editEntry();
    void removeEntry();
    void slot_init();

signals:

    void signal_update();
private:
     myStandardItemModel * switchTableModel;
     QTableView *tableview;

     QHBoxLayout *bottom_layout;
     QVBoxLayout *mainLayout;
};

#endif // SWITCHMANAGE_H
