#ifndef ALARMTHRESHSET_H
#define ALARMTHRESHSET_H

#include <QWidget>
#include <QSqlQuery>
#include "mystandarditemmodel.h"

namespace Ui {
class AlarmThreshSet;
}

class AlarmThreshSet : public QWidget
{
    Q_OBJECT
    
public:
    explicit AlarmThreshSet(QWidget *parent = 0);
    ~AlarmThreshSet();

private:
    Ui::AlarmThreshSet *ui;

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
    myStandardItemModel * threshTableModel;
     myStandardItemModel * singleThreshTableModel;
      void init_table();

      QSqlQuery *sqlquery;

};

#endif // ALARMTHRESHSET_H






