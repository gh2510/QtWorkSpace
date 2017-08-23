#ifndef NEWALARMTHRESHSET_H
#define NEWALARMTHRESHSET_H

#include <QWidget>
#include <QSqlQuery>
#include "mystandarditemmodel.h"

namespace Ui {
class NewAlarmThreshSet;
}

class NewAlarmThreshSet : public QWidget
{
    Q_OBJECT

public:
    explicit NewAlarmThreshSet(QWidget *parent = 0);
    ~NewAlarmThreshSet();
    void iniView();
    void init_table();
    void setViewSize();

public slots:
    void addEntry();
    void addEntry(QString alarmname,QString threshedit);
    //void editEntry();
    void editEntry(QModelIndex index);  //yangmeng 161026 改为双列显示
    void removeEntry();
    void addSingleEntry();
    void delSingleEntry();
    void editSingleEntry();

signals:
    void alarmSet(QString,int,int,double);  // gaohao Add 修改特定阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输出） 阈值信息
    void alarmDel(QString,int,int); // gaohao Add 删除特定阈值时发送 分别时交换机名称 端口号 输入输出属性（0为输入 1为输的
    void alarmAdd(QString,int,int,double);      //yangmeng 161101

private:
    Ui::NewAlarmThreshSet *ui;
    myStandardItemModel * threshTableModel;
    myStandardItemModel * singleThreshTableModel;
    QSqlQuery *sqlquery;
};

#endif // NEWALARMTHRESHSET_H
