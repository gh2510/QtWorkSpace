#ifndef NEWSWITCHMANAGE_H
#define NEWSWITCHMANAGE_H

#include <QWidget>
#include "mystandarditemmodel.h"

namespace Ui {
class NewSwitchManage;
}

class NewSwitchManage : public QWidget
{
    Q_OBJECT

public:
    explicit NewSwitchManage(QWidget *parent = 0);
    ~NewSwitchManage();
    void iniView();
    void iniModel();
    void setManageBtnVisible(bool isVisibled);

public slots:
    void addEntry();
    void editEntry();
    void editEntry(QModelIndex);
    void removeEntry();
    void slot_init();

signals:
    void signal_update();

private:
    Ui::NewSwitchManage *ui;
    myStandardItemModel * switchTableModel;
};

#endif // NEWSWITCHMANAGE_H
