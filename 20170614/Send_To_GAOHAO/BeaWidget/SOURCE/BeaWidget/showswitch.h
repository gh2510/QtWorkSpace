#ifndef SHOWSWITCH_H
#define SHOWSWITCH_H

#include <QWidget>
#include <QDialog>
#include<QTableView>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"mystandarditemmodel.h"
#include"commonbutton.h"

namespace Ui {
class ShowSwitch;
}

class ShowSwitch : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShowSwitch(QWidget *parent = 0);
    ~ShowSwitch();
    void init_table();
public slots:
    void slot_close();
private:
    Ui::ShowSwitch *ui;
    myStandardItemModel * switchTableModel;
    QTableView *tableview;
    commonButton *btn_ok;
    QHBoxLayout *bottom_layout;
    QVBoxLayout *mainLayout;
};

#endif // SHOWSWITCH_H
