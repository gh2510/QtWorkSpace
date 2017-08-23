#ifndef PERFORMANCEPAGE_H
#define PERFORMANCEPAGE_H

#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QList>
#include "mystandarditemmodel.h"
#include "commonbutton.h"
class PerformancePage : public QWidget
{
    Q_OBJECT
public:
    explicit PerformancePage(QWidget *parent = 0);
    ~PerformancePage();
    void SetTableView(QString sql_txt,QStringList title_txt,QList<int> title_width);
signals:

public slots:
    void OnPrevButtonClick();    //prve page
    void OnNextButtonClick();    //next page
    void OnSwitchPageButtonClick();  //go page
    void OnFirstButtonClick();
    void OnLastButtonClick();
private:
       void InitWindow();
       int  GetTotalRecordCount();     //得到记录数
       int  GetPageCount();          //得到页数
       void RecordQuery(int limitIndex); //记录查询
       void UpdateStatus();       //刷新状态
       void SetTotalPageLabel(); //设置总数页文本
private:
     myStandardItemModel    *queryModel;  //查询模型
     QTableView    *tableView; //数据表
     QLabel    *totalPageLabel; //总数页文本
     QLabel    *currentPageLabel; //当前页文本
     QLineEdit *switchPageLineEdit; //转到页输入框
     commonButton   *prevButton;      //前一页按钮
     commonButton   *nextButton;      //下一页按钮
     commonButton   *firstButton;      //前一页按钮
     commonButton   *lastButton;      //下一页按钮
     commonButton   *switchPageButton;    //转到页按钮
     QHBoxLayout *bottom_layout;
     QVBoxLayout *main_layout;
     QLabel *switchpage;
     QLabel*page;
     QStringList table_title;
     QList<int>  table_width;

     QString sql;
     int       currentPage;      //当前页
     int       totalPage;    //总页数
     int       totalRecrodCount;     //总记录数
     enum      {PageRecordCount = 12};//每页显示记录数，原设15，但会出现竖直的卷滚条，qhy--2016.11.06
    
};

#endif // PERFORMANCEPAGE_H
