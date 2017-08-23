#ifndef NEWERRORMANAGE_H
#define NEWERRORMANAGE_H

#include <QWidget>
#include "mystandarditemmodel.h"

namespace Ui {
class NewErrorManage;
}

class NewErrorManage : public QWidget
{
    Q_OBJECT

public:
    explicit NewErrorManage(QWidget *parent = 0);
    ~NewErrorManage();
    void iniView();
    void init_table();
    void setViewSize();
    void setManageBtnVisible(bool isVisibled);

public slots:
    void editEntry();
    void addEntry();
    void removeEntry();
    void showEntry();
    void slot_init();

private:
    Ui::NewErrorManage *ui;
    myStandardItemModel * switchTableModel;
};

#endif // NEWERRORMANAGE_H
