#ifndef NEWALARMHISTORY_H
#define NEWALARMHISTORY_H

#include <QWidget>
#include <QSqlTableModel>

#include "mystandarditemmodel.h"
#include "calendar_dialog.h"

namespace Ui {
class NewAlarmHistory;
}

class NewAlarmHistory : public QWidget
{
    Q_OBJECT

public:
    explicit NewAlarmHistory(QWidget *parent = 0);
    ~NewAlarmHistory();
    void initSearchWidget();
    void initTableView();
    void SetTableView(QString sql_txt,QStringList title_txt,QList<int> title_width);
    void RecordQuery(int limitIndex);

private:
    int  GetTotalRecordCount();     //得到记录数
    int  GetPageCount();            //得到页数
    void UpdateStatus();            //刷新状态

public slots:
   void slot_search();
   void slot_clearTime();
   void slot_clearData();

  void showcalendar();
  void setdate(const QDate&);

   void OnPrevButtonClick();        //prve page
   void OnNextButtonClick();        //next page
   void OnFirstButtonClick();       //prve page
   void OnLastButtonClick();        //next page
   void OnSwitchPageButtonClick();  //go page
   void valueChanged(QString);      //state Change
   void slot_search_res(QString,QString,QString,QString,QString);

signals:
    void signal_search(QString,QString,QString,QString,QString);

private:
    Ui::NewAlarmHistory *ui;
    CalendarDialog *calendar;
    QString dateBtnName;
    myStandardItemModel    *queryModel;  //查询模型
    QStringList table_title;
    QList<int>  table_width;             //表的各个字段宽度，数组

    QString pre_sql;
    QStringList ql;
    QList<int> qi;

    QString sql;
    QString conditionSql;
    int currentPage;              //当前页
    int totalPage;                //总页数
    int totalRecrodCount;         //总记录数
    enum {PageRecordCount = 12};  //每页显示记录数
};

#endif // NEWALARMHISTORY_H
