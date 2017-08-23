#include "newperformancesearch.h"
#include "ui_newperformancesearch.h"
#include <QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
#include"connection.h"
#include"insertthread.h"

NewPerformanceSearch::NewPerformanceSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPerformanceSearch)
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"初始化 NewPerformanceSearch"
           <<"\n";
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget->setFixedSize(this->width(),this->height());
    ui->tableView->setFixedWidth(ui->widget->width());
    ui->widget_title->setFixedHeight(100);

    this->sql="";
    currentPage = 0;
    totalRecrodCount=0;
    totalPage=0;
    queryModel =NULL;
    calendar = NULL;
    if(!queryModel)
    {
        queryModel=new myStandardItemModel();
    }
    iniView();

    pre_sql="select switchname, time, type,value, state from performance limit 0 ";

    ql<<"交换机名"<<"时间"<<"性能项"<<"数值"<<"状态";
    int wi=ui->tableView->width()/5-2;
    qi<<wi<<wi<<wi<<wi<<wi;
    SetTableView(pre_sql,ql,qi);

    QSqlQuery sqlquery("",DBConnection::db);
    sqlquery.exec("select  name from switch");
    while(sqlquery.next())
    {
        ui->switchName->addItem(sqlquery.value(0).toString());
    }

    for(int i=1;i<=60;i++)
    {
        ui->port->addItem(QString::number(i));
    }
    sqlquery.finish();
    sqlquery.clear();
    ui->port->setEnabled(false);

    connect(ui->search,SIGNAL(clicked()),this,SLOT(slot_search()));
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(slot_clear()));
    connect(ui->clearTime,SIGNAL(clicked()),this,SLOT(slot_clearTime()));
    connect(ui->alarmClass,SIGNAL(currentIndexChanged(QString)),this,SLOT(slot_setPort(QString)));
    connect(ui->prevButton,SIGNAL(clicked()),this,SLOT(OnPrevButtonClick()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(OnNextButtonClick()));
    connect(ui->switchPageButton,SIGNAL(clicked()),this,SLOT(OnSwitchPageButtonClick()));
    connect(ui->firstButton,SIGNAL(clicked()),this,SLOT(OnFirstButtonClick()));
    connect(ui->lastButton,SIGNAL(clicked()),this,SLOT(OnLastButtonClick()));
    connect(ui->starttimeBtn,SIGNAL(clicked()),this,SLOT(showcalendar()));
    connect(ui->endtimeBtn,SIGNAL(clicked()),this,SLOT(showcalendar()));
    connect(this,SIGNAL(signal_search(QString,QString,QString,QString,QString,QString)),
            this,SLOT(slot_search_res(QString,QString,QString,QString,QString,QString)));

}

void NewPerformanceSearch::iniView()
{
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(queryModel);
}

void NewPerformanceSearch::SetTableView(QString sql_txt, QStringList title_txt, QList<int> title_width)
{
    this->sql=sql_txt;
    this->table_title=title_txt;
    this->table_width=title_width;

    RecordQuery(0);//执行查询语句
    totalRecrodCount=GetTotalRecordCount();
    totalPage=GetPageCount();
    if ( totalPage == 0 )     //After query, initiate the currentPage, if there is no data ,set current page 0, otherwise set 1
        currentPage = 0;
    else
    {
       currentPage = 1;
    }
    UpdateStatus();

//    for(int i=0;i<table_width.count()-1;i++)
//    {
//        ui->tableView->setColumnWidth(i,this->table_width.at(i));    //如果需要显示竖直卷滚条，宽度需要-4，才能不出现横向卷滚条 qhy，2016.11.06
//    }
}

void NewPerformanceSearch::slot_search()
{
    QString date_st = ui->starttime->text();
    QString date_ed = ui->endtime->text();
    QString swi_name = ui->switchName->currentText();
    QString type = ui->alarmClass->currentText();
    QString performanceState = ui->state->currentText();
    QString currentPort = ui->port->currentText();

    emit signal_search(swi_name,
                       type,
                       date_st,
                       date_ed,
                       performanceState,
                       currentPort);
}

void NewPerformanceSearch::slot_clearTime()
{
    ui->starttime->clear();
    ui->endtime->clear();
}

void NewPerformanceSearch::slot_setPort(QString text)
{
    if(text=="端口进速率"||text=="端口出速率")
    {
        ui->port->setEnabled(true);
    }else
    {
        ui->port->setEnabled(false);
        ui->port->setCurrentIndex(0);
    }
}

void NewPerformanceSearch::OnPrevButtonClick()
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

void NewPerformanceSearch::OnNextButtonClick()
{
    int limitIndex = currentPage * PageRecordCount;
    //当前页小于总页数，才能向后翻页---qhy 2016.10.27
    if (currentPage < totalPage && totalPage >0)
    {
        RecordQuery(limitIndex);
        currentPage += 1;
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

void NewPerformanceSearch::OnFirstButtonClick()
{
    RecordQuery(0);
    currentPage = 1;
    UpdateStatus();
}

void NewPerformanceSearch::OnLastButtonClick()
{
    RecordQuery((totalPage-1) * PageRecordCount);
    currentPage = totalPage;
    UpdateStatus();
}

void NewPerformanceSearch::showcalendar()
{
    QString btnName = QObject::sender()->objectName();
    if(btnName == ui->starttimeBtn->objectName())
    {
        isFirst = true;
    }
    else if(btnName == ui->endtimeBtn->objectName())
    {
        isFirst = false;
    }
    if(!calendar)
    {
        calendar = new CalendarDialog();
    }
    calendar->setMinimumSize(400,150);
    calendar->move(QCursor::pos().x()-180,QCursor::pos().y()+ ui->starttimeBtn->height());
    connect(calendar,SIGNAL(checkdate(const QDate&)),this,SLOT(setdate(const QDate&)));
    calendar->show();
}

void NewPerformanceSearch::setdate(const QDate& date_checked)
{
    QDate date=date_checked;
    QString datestr=date.toString("yyyy-MM-dd");
    if(isFirst)
    {
        ui->starttime->setText(datestr);
        ui->starttime->setFocus();
    }
    else
    {
        ui->endtime->setText(datestr);
        ui->starttime->setFocus();
    }

    calendar->close();
}

void NewPerformanceSearch::OnSwitchPageButtonClick()
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

void NewPerformanceSearch::slot_search_res(QString name,QString alam_type,QString da_st,QString da_ed,QString state,QString currentPort)
{
    QString sql = "select switchname, time, type,value, state from performance";
    QString n_sql=" 2>1 ";
//    bool flag=false;
    QString da_end=da_ed.left(8)+
            QString::number(da_ed.right(2).toInt()+1);//结束时间后移一天，能够查到和结束时间同在一天的字段
    if(name!=NULL &&name.trimmed()!="")
    {

       n_sql+=" and switchname='"+name+"'";
    }

    if(state!=NULL &&state.trimmed()!="")
    {
       n_sql+=" and state='"+state+"'";
    }


    if(alam_type!=NULL &&alam_type.trimmed()!="")
    {
        if(alam_type=="端口进速率")
        {
            if (currentPort>0 )
            {
                alam_type="端口"+currentPort+"进速率";
                n_sql+= " and type ='"+alam_type+"'";
            }
            else
            {
                // n_sql+= " and type ='"+alam_type+"'";
                n_sql += " and type like '%进速率' ";
            }
        }
        else  if (alam_type=="端口出速率"  )
        {
             if (currentPort>0 )
             {
                 alam_type="端口"+currentPort+"出速率";
                 n_sql+= " and type ='"+alam_type+"'";
             }
             else
             {
                n_sql += " and type like '%出速率' ";
             }

        }
        //由于表中记录了端口号，不能直接查询------qhy， 2016.11.07
        else if ( alam_type=="端口状态"  )
        {
              n_sql += " and type like '%状态' ";
        }
        else
        {
              n_sql+= " and type ='"+alam_type+"'";
        }
    }

    //startup time
    if(da_st!=NULL &&da_st.trimmed()!="")
    {
       n_sql+=" and time >= '"+da_st+"'";
    }

    //end time
    if(da_ed!=NULL &&da_ed.trimmed()!="")
    {
       n_sql+=" and time <= '"+da_end+"'";
    }
    sql+=" where "+n_sql;
    sql+=" order by time desc";
    SetTableView(sql,ql,qi);
}

void NewPerformanceSearch::slot_clear()
{
    QSqlQuery query("",db_sqlite);
    query.exec("delete  from performance");
    SetTableView("select switchname,time,type,value,state from performance ",ql,qi);
}

int  NewPerformanceSearch::GetTotalRecordCount()
{
    QString sql_get_num=this->sql.mid(sql.indexOf("from"));
    sql_get_num=QString("select count(*) ")+sql_get_num;
    QSqlQuery sqlquery("",db_sqlite);
    sqlquery.exec(sql_get_num);
    sqlquery.next();
    int tmp= sqlquery.value(0).toInt();
    sqlquery.finish();
    return tmp;

}

int NewPerformanceSearch::GetPageCount()
{
    if (totalRecrodCount ==0 )
        return 0 ;   //没有记录，返回总页数为0
    else
       return (totalRecrodCount % PageRecordCount == 0) ? (totalRecrodCount / PageRecordCount) : (totalRecrodCount / PageRecordCount + 1);
}

void NewPerformanceSearch::RecordQuery(int limitIndex)
{
    QSqlQuery query("",db_sqlite);
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
        ui->tableView->setRowHeight(itemCount,ui->tableView->height()/12-2);
        itemCount++;
    }

    query.finish();

    for(int i=0;i<table_width.count()-1;i++)
    {
        ui->tableView->setColumnWidth(i,this->table_width.at(i));    //如果需要显示竖直卷滚条，宽度需要-4，才能不出现横向卷滚条 qhy，2016.11.06
    }

}

void NewPerformanceSearch::UpdateStatus()
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
    if (totalPage > 0)
    {
        if (currentPage==1)
        {
            ui->prevButton->setEnabled(false);
            ui->nextButton->setEnabled(true);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
        else if (currentPage==totalPage)
        {
            ui->prevButton->setEnabled(true);
            ui->nextButton->setEnabled(false);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
        else if (currentPage<totalPage)
        {
            ui->prevButton->setEnabled(true);
            ui->nextButton->setEnabled(true);
            ui->firstButton->setEnabled(true);
            ui->lastButton->setEnabled(true);
        }
    }
}

NewPerformanceSearch::~NewPerformanceSearch()
{
    delete ui;
//    if(queryModel) delete queryModel;
//    if(calendar) delete calendar;
}


