#ifndef NEWPERFORMANCESEARCH_H
#define NEWPERFORMANCESEARCH_H

#include <QWidget>
#include <QSqlTableModel>
#include <QList>

#include "mystandarditemmodel.h"
#include "calendar_dialog.h"

namespace Ui {
class NewPerformanceSearch;
}

class NewPerformanceSearch : public QWidget
{
    Q_OBJECT

public:
    explicit NewPerformanceSearch(QWidget *parent = 0);
    ~NewPerformanceSearch();
    void iniView();
    void SetTableView(QString sql_txt,QStringList title_txt,QList<int> title_width);

public slots:
    void  slot_search();
    void  slot_clear();
    void  slot_clearTime();
    void  slot_setPort(QString text);

    void OnPrevButtonClick();           //prve page
    void OnNextButtonClick();           //next page
    void OnSwitchPageButtonClick();     //go page
    void OnFirstButtonClick();
    void OnLastButtonClick();

    void showcalendar();
    void setdate(const QDate&date_checked);

    void slot_search_res(QString,QString,QString,QString,QString,QString);

signals:
    void signal_search(QString,QString,QString,QString,QString,QString);
     void signal_clear();

private:
    Ui::NewPerformanceSearch *ui;
    int  GetTotalRecordCount();         //得到记录数
    int  GetPageCount();                //得到页数
    void RecordQuery(int limitIndex);   //记录查询
    void UpdateStatus();                //刷新状态

    QString pre_sql;
    QStringList ql;
    QList<int> qi;

    myStandardItemModel    *queryModel;  //查询模型
    QStringList table_title;
    QList<int>  table_width;

    CalendarDialog *calendar;
    bool isFirst;

    QString sql;
    int currentPage;              //当前页
    int totalPage;                //总页数
    int totalRecrodCount;         //总记录数
    enum{PageRecordCount = 12};   //每页显示记录数，原设15，但会出现竖直的卷滚条，qhy--2016.11.06
};

#endif // NEWPERFORMANCESEARCH_H
