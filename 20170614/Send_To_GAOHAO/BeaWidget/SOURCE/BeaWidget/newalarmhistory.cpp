#include "newalarmhistory.h"
#include "ui_newalarmhistory.h"

#include <qheaderview.h>
#include <QLineEdit>
#include <QComboBox>
#include <QCalendarWidget>
#include <QDate>
#include <QDialog>
#include <QString>
#include <QTextCharFormat>
#include <QCursor>
#include <QLocale>
#include <QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
#include"connection.h"
#include <QDebug>

NewAlarmHistory::NewAlarmHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAlarmHistory)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    calendar = NULL;
    this->sql="";
    currentPage = 0;
    totalRecrodCount=0;
    totalPage=0;
    initSearchWidget();
    initTableView();

    pre_sql="select name,alarmtype,value, starttime,lasttime,isdeal from alarm ";  //
    QString ini_sql="select name,alarmtype,value,starttime,lasttime,isdeal from alarm order by starttime desc ";   //限定为只查12条，从开始记录起 limit 0,12
    ql<<"交换机名"<<"警告类型"<<"报警数值"<< "开始时间"<<"结束时间"<<"是否处理";  //
    int wi=ui->tableView->width()/7 ; // 如需要显示竖直卷滚条，宽度需要 -3;
    qi<<wi-20<<wi<<wi-20<<wi<<wi<<wi-4;
    SetTableView(ini_sql,ql,qi);

    connect(this,SIGNAL(signal_search(QString,QString,QString,QString,QString)),this,SLOT(slot_search_res(QString,QString,QString,QString,QString)));

    connect(ui->prevButton,SIGNAL(clicked()),this,SLOT(OnPrevButtonClick()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(OnNextButtonClick()));
    connect(ui->firstButton,SIGNAL(clicked()),this,SLOT(OnFirstButtonClick()));
    connect(ui->lastButton,SIGNAL(clicked()),this,SLOT(OnLastButtonClick()));
    connect(ui->switchPageButton,SIGNAL(clicked()),this,SLOT(OnSwitchPageButtonClick()));

    connect(ui->starttimeBtn,SIGNAL(clicked()),this,SLOT(showcalendar()));
    connect(ui->endtimeBtn,SIGNAL(clicked()),this,SLOT(showcalendar()));

    connect(ui->switchName,SIGNAL(currentIndexChanged(QString)),this,SLOT(valueChanged(QString)));
    connect(ui->alarmClass,SIGNAL(currentIndexChanged(QString)),this,SLOT(valueChanged(QString)));
    connect(ui->isConfirmed,SIGNAL(currentIndexChanged(QString)),this,SLOT(valueChanged(QString)));
    connect(ui->starttime,SIGNAL(textChanged(QString)),this,SLOT(valueChanged(QString)));
    connect(ui->endtime,SIGNAL(textChanged(QString)),this,SLOT(valueChanged(QString)));

}


//初始化条件查询窗口
void NewAlarmHistory::initSearchWidget()
{
    QSqlQuery sqlquery("",DBConnection::db);
    sqlquery.exec("select  name from switch");
    while(sqlquery.next())
    {
        ui->switchName->addItem(sqlquery.value(0).toString());
    }

    sqlquery.exec("select  alarmtype from alarmquery");
    while(sqlquery.next())
    {
        ui->alarmClass->addItem(sqlquery.value(0).toString());
    }
    sqlquery.clear();
    connect(ui->search,SIGNAL(clicked()),this,SLOT(slot_search()));
    connect(ui->clearTime,SIGNAL(clicked()),this,SLOT(slot_clearTime()));
    connect(ui->clearData,SIGNAL(clicked()),this,SLOT(slot_clearData()));
}

//初始化表格
void NewAlarmHistory::initTableView()
{
    queryModel=new myStandardItemModel;
    ui->tableView->setModel(queryModel);
    ui->tableView->setFixedHeight(this->height()*7.5/10);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

//查询需要的页数上要显示的数据
void NewAlarmHistory::RecordQuery(int limitIndex)
{
    QSqlQuery query("",DBConnection::db);
    QString sql_t;
    sql_t=sql+QString(" limit %1,%2").arg(limitIndex).arg(QString::number(PageRecordCount));
    query.exec(sql_t);

    int itemCount=0;
    queryModel->clear();
    for(int i=0;i<table_title.count();i++)
    {
         queryModel->setHorizontalHeaderItem(i,new QStandardItem(this->table_title.at(i)));
    }
    while(query.next())
    {
        for(int i=0;i<table_title.count();i++)
        {
            queryModel->setItem(itemCount,i,new QStandardItem(query.value(i).toString()));
        }
        ui->tableView->setRowHeight(itemCount,(ui->tableView->height()-ui->tableView->horizontalHeader()->height())/12);
        itemCount++;
    }

    for(int i=0;i<table_width.count();i++)
    {
        ui->tableView->setColumnWidth(i,this->table_width.at(i));
    }
    query.finish();
}

void NewAlarmHistory::showcalendar()
{
    this->dateBtnName = QObject::sender()->objectName();
    if(!calendar)
    {
        calendar = new CalendarDialog();
    }
    calendar->setMinimumSize(400,150);
    calendar->move(QCursor::pos().x()-180,QCursor::pos().y()+ ui->starttimeBtn->height());
    connect(calendar,SIGNAL(checkdate(const QDate&)),this,SLOT(setdate(const QDate&)));
    calendar->show();
}

void NewAlarmHistory::setdate(const QDate& date_checked)
{
    QDate date=date_checked;
    QString datestr=date.toString("yyyy-MM-dd");
    if(dateBtnName == ui->starttimeBtn->objectName())
    {
        ui->starttime->setText(datestr);
        ui->starttime->setFocus();
    }
    else
    {
        ui->endtime->setText(datestr);
        ui->endtime->setFocus();
    }
    calendar->close();
}

void NewAlarmHistory::slot_search_res(QString name,QString alam_type,QString iscom,QString da_st,QString da_ed)
{
    QString sql;
    QString n_sql=" 2>1 ";
    //bool flag=false;
    QString da_end=da_ed.left(8)+
            QString::number(da_ed.right(2).toInt()+1);//结束时间后移一天，能够查到和结束时间同在一天的字段
    if(name!=NULL &&name.trimmed()!="")
    {
        n_sql+=" and name='"+name+"'";
    }
    if(alam_type!=NULL &&alam_type.trimmed()!="")
    {
        if ( alam_type == "温度过高")
            n_sql+=" and alarmtype='CPU"+alam_type+"'";
        else if (alam_type != "端口速率过高")
          n_sql+=" and alarmtype='"+alam_type+"'";
        else
          n_sql+= " and alarmtype like '%速率过高%'";
    }
    if(iscom!=NULL &&iscom.trimmed()!="")
    {
        n_sql+=" and isdeal='"+iscom+"'";
    }

    if(da_st!=NULL &&da_st.trimmed()!="")
    {
       n_sql+=" and starttime >= '"+da_st+"'";
    }
    if(da_ed!=NULL &&da_ed.trimmed()!="")
    {
        n_sql+=" and (lasttime <= '"+da_end+"' or lasttime is null)";
    }
    sql=pre_sql+" where "+n_sql;
    conditionSql = n_sql;//记录查询条件

    sql+="  order by starttime desc";  //限定为只查12条，从开始记录起
    qDebug()<<"sql:   "<<sql;
    SetTableView(sql,ql,qi);
}

void NewAlarmHistory::SetTableView(QString sql_txt,QStringList title_txt,QList<int> title_width)
{
    this->sql=sql_txt;

    qDebug()<<"this.sql:  " << this->sql <<endl;

    this->table_title=title_txt;
    this->table_width=title_width;

    RecordQuery(0);//执行查询语句
    totalRecrodCount=GetTotalRecordCount();
    qDebug()<<"totalRecrodCount:  "<<totalRecrodCount;
    totalPage=GetPageCount();
    qDebug()<<"totalPage:  "<<totalPage;
    if ( totalPage == 0 )     //After query, initiate the currentPage, if there is no data ,set current page 0, otherwise set 1
        currentPage = 0;
    else
        currentPage = 1;
    UpdateStatus();
}

//点击上一页时的处理
void NewAlarmHistory::OnPrevButtonClick()
{
    int limitIndex = (currentPage - 2) * PageRecordCount;
    //当前页大于1，才能向前翻页---qhy 2016.10.27
    if (currentPage>1 && totalPage >0)
    {
        RecordQuery(limitIndex);
        currentPage -= 1;
    }
    else
    {
        if (totalPage==0 )
        {
            currentPage = 0;
        }

    }
    UpdateStatus();
}

//点击下一页时的处理
void NewAlarmHistory::OnNextButtonClick()
{
    int limitIndex = currentPage * PageRecordCount;
    //当前页小于总页数，才能向后翻页---qhy 2016.10.27
    if ( currentPage < totalPage && totalPage >0 )
    {
        RecordQuery(limitIndex);
        currentPage += 1;
    }
    else
    {
        if (totalPage == 0)
        {
            currentPage = 0;
        }

    }
    UpdateStatus();
}

//点击首页时的处理
void NewAlarmHistory::OnFirstButtonClick()
{
    RecordQuery(0);
    if (totalPage == 0)
    {
        currentPage = 0;
    }
    else
    {
        currentPage = 1;
    }
    UpdateStatus();
}

//点击尾页时的处理
void NewAlarmHistory::OnLastButtonClick()
{
    RecordQuery((totalPage-1) * PageRecordCount);
    currentPage = totalPage;
    UpdateStatus();
}

//跳转到输入的要查询的页码时的处理
void NewAlarmHistory::OnSwitchPageButtonClick()
{
    //得到输入字符串
    QString szText = ui->switchPageLineEdit->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
       QMessageBox::information(0, tr("提示"), tr("请输入数字"));
       return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(0, tr("提示"), tr("请输入跳转页面"));
        return;
    }
    //得到页数
    int pageIndex = szText.toInt();
    //判断是否有指定页
    if(pageIndex > totalPage || pageIndex < 1)
    {
        QMessageBox::information(0, tr("提示"), tr("没有指定的页面，请重新输入"));
        return;
    }
    //得到查询起始行号
    int limitIndex = (pageIndex-1) * PageRecordCount;
    //记录查询
    RecordQuery(limitIndex);
    //设置当前页
    currentPage = pageIndex;
    //刷新状态
    UpdateStatus();
}

//任意查询条改变后禁用清除
void NewAlarmHistory::valueChanged(QString)
{
    qDebug()<<"value changed";
    ui->clearData->setEnabled(false);
    ui->clearData->setStyleSheet("color: white;border-radius: 8px;border-image: url(:/images/images/button_gray.png);");
}

//得到符合查询条件的总的记录数
int NewAlarmHistory::GetTotalRecordCount()
{
    QString sql_get_num=this->sql.mid(sql.indexOf("from"));
    sql_get_num=QString("select count(*) ")+sql_get_num;
    QSqlQuery sqlquery("",DBConnection::db);
    sqlquery.exec(sql_get_num);
    sqlquery.next();
    int tmp= sqlquery.value(0).toInt();
    sqlquery.finish();
    return tmp;
}

//得到符合查询条件的记录总页数
int NewAlarmHistory::GetPageCount()
{
  if (totalRecrodCount ==0 )
      return 0 ;   //没有记录，返回总页数为0
  else
      return (totalRecrodCount % PageRecordCount == 0) ? (totalRecrodCount / PageRecordCount) : (totalRecrodCount / PageRecordCount + 1);
}

void NewAlarmHistory::UpdateStatus()
{
    if ( totalPage == 0 )
    {
        currentPage = 0;  //如果没有数据，为0页
        ui->prevButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->firstButton->setEnabled(false);
        ui->lastButton->setEnabled(false);
    }
    QString szCurrentText = QString("当前第%1页").arg(QString::number(currentPage));
    ui->currentPageLabel->setText(szCurrentText);
    QString szPageCountText = QString("总共%1页").arg(QString::number(totalPage));
    ui->totalPageLabel->setText(szPageCountText);
    if (totalPage > 0 )
    {
        if (currentPage == 1)
        {
            ui->prevButton->setEnabled(false);
            ui->nextButton->setEnabled(true);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
        else if (currentPage == totalPage)
        {
            ui->prevButton->setEnabled(true);
            ui->nextButton->setEnabled(false);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
        else if ( currentPage < totalPage)
        {
            ui->prevButton->setEnabled(true);
            ui->nextButton->setEnabled(true);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
     }
}

//点击查询按钮后发出查询信号
void NewAlarmHistory::slot_search()
{
    QString date_st=ui->starttime->text();
    QString date_ed=ui->endtime->text();
    QString iscom=ui->isConfirmed->currentText();
    QString swi_name=ui->switchName->currentText();
    QString alarm=ui->alarmClass->currentText();

    //数据库条件查询并更新搜索结果
    emit signal_search(swi_name,alarm,iscom,date_st,date_ed);
    ui->clearData->setEnabled(true);//查询后启用清除
    ui->clearData->setStyleSheet("color: white;border-radius: 8px;border-image: url(:/images/images/button_search.png);");
}

//清空时间按钮的操作
void NewAlarmHistory::slot_clearTime()
{
    ui->starttime->clear();
    ui->endtime->clear();
}

//清空数据，逻辑待增加
void NewAlarmHistory::slot_clearData()
{
    QSqlQuery query("",DBConnection::db);
    QString deleteSql = "delete from alarm where" + conditionSql;
    qDebug()<<"deleteSql:"<<deleteSql;
    bool ifUse = query.exec(deleteSql);
    qDebug()<<"clear data now:"<<ifUse;
    SetTableView(this->sql,ql,qi);
}

NewAlarmHistory::~NewAlarmHistory()
{
    delete ui;
    if(calendar)delete calendar;
}



