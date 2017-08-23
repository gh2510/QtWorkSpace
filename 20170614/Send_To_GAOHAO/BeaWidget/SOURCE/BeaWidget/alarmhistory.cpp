#include "alarmhistory.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

alarmHistory::alarmHistory(QWidget *parent) :
    QWidget(parent)
{
    main_layout = new QVBoxLayout();
    searchAlarm = new search_alarm();
    alarmTable = new MyPageTableview();
    pre_sql="select name,alarmtype,value, starttime,lasttime,isdeal from alarm ";  //
    QString ini_sql="select name,alarmtype,value,starttime,lasttime,isdeal from alarm order by starttime desc ";   //限定为只查12条，从开始记录起 limit 0,12
    ql<<"交换机名"<<"警告类型"<<"报警数值"<< "开始时间"<<"结束时间"<<"是否处理";  //
    int wi=QApplication::desktop()->width()/7 ; // 如需要显示竖直卷滚条，宽度需要 -3;
    qi<<wi-20<<wi<<wi-20<<wi<<wi<<wi-4;
    alarmTable->SetTableView(ini_sql,ql,qi);
    setFixedHeight(QApplication::desktop()->height()*7/8);

    main_layout->addWidget(searchAlarm,0,Qt::AlignTop|Qt::AlignHCenter);
    main_layout->addWidget(alarmTable,0,Qt::AlignHCenter);
    main_layout->setSpacing(5);
    this->setLayout(main_layout);

    connect(searchAlarm,SIGNAL(signal_search(QString,QString,QString,QString,QString)),this,SLOT(slot_search_res(QString,QString,QString,QString,QString)));

}

alarmHistory::~alarmHistory()
{

    if(searchAlarm)delete searchAlarm;
    if(alarmTable)delete alarmTable;
    if(main_layout)delete main_layout;
}

void alarmHistory::slot_search_res(QString name,QString alam_type,QString iscom,QString da_st,QString da_ed)
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

    sql+="  order by starttime desc";  //限定为只查12条，从开始记录起
    qDebug()<<"sql:   "<<sql;
     alarmTable->SetTableView(sql,ql,qi);
}
