#include"performancesearch.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include"insertthread.h"
PerformanceSearch::PerformanceSearch(QWidget *parent) :
    QWidget(parent)
{
    main_layout = new QVBoxLayout();
    searchAlarm=new Search_performance();
    alarmTable = new PerformancePage();
    pre_sql="select switchname, time, type,value, state from performance limit 0 ";

    ql<<"交换机名"<<"时间"<<"性能项"<<"数值"<<"状态";
    int wi=QApplication::desktop()->width()/6;
    qi<<wi<<wi<<wi<<wi<<wi;
    alarmTable->SetTableView(pre_sql,ql,qi);
   setFixedHeight(QApplication::desktop()->height()*7/8);

    main_layout->addWidget(searchAlarm,0,Qt::AlignTop|Qt::AlignHCenter);
    main_layout->addWidget(alarmTable,0,Qt::AlignHCenter);
    main_layout->setSpacing(5);
    this->setLayout(main_layout);

    connect(searchAlarm,SIGNAL(signal_search(QString,QString,QString,QString,QString,QString)),this,SLOT(slot_search_res(QString,QString,QString,QString,QString,QString)));
    connect(searchAlarm,SIGNAL(signal_clear()),this,SLOT(slot_clear()));

}


void PerformanceSearch::slot_search_res(QString name,QString alam_type,QString da_st,QString da_ed,QString state,QString currentPort)
{
    QString sql = "select switchname, time, type,value, state from performance";
    QString n_sql=" 2>1 ";
    bool flag=false;
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
        if(alam_type=="端口进速率") {
            if (currentPort>0 )
            { alam_type="端口"+currentPort+"进速率";
                 n_sql+= " and type ='"+alam_type+"'";
            }else
              // n_sql+= " and type ='"+alam_type+"'";
                n_sql += " and type like '%进速率' ";
        }else  if (alam_type=="端口出速率"  ) {
             if (currentPort>0 ){
                 alam_type="端口"+currentPort+"出速率";
                 n_sql+= " and type ='"+alam_type+"'";
                 }
             else
                 n_sql += " and type like '%出速率' ";
        }else if ( alam_type=="端口状态"  ) {        //由于表中记录了端口号，不能直接查询------qhy， 2016.11.07
              n_sql += " and type like '%状态' ";
        }else
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
    alarmTable->SetTableView(sql,ql,qi);
}



void PerformanceSearch::slot_clear()
{
    QSqlQuery query("",db_sqlite);
    query.exec("delete  from performance");
    alarmTable->SetTableView("select switchname,time,type,value,state from performance ",ql,qi);
}
PerformanceSearch::~PerformanceSearch()
{
    delete ui;
    if(searchAlarm)delete searchAlarm;
    if(alarmTable)delete alarmTable;
    if(main_layout)delete main_layout;
}
