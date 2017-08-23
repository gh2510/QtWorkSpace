#include "monitorwidget.h"
#include "ui_MonitorWidget.h"
#include <QSqlQuery>
#include <QScrollArea>
#include <QApplication>
#include <QDesktopWidget>
#include "connection.h"
#define FLASH_LIST_H QApplication::desktop()->height()*4/6

int Listheight=0;
MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorWidget)
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"初始化 MonitorWidget"
           <<"\n";
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget_list->setFixedSize(120,this->height());
    ui->widget_2->setFixedSize(this->width()-120,this->height());
    ui->widget_show->setFixedSize(ui->widget_2->width(),ui->widget_2->height());
    ui->tabWidget->setFixedSize(ui->widget_2->width()*9.8/10,ui->widget_2->height());

    Listheight = ui->widget_list->height()*8/10;

    QFont font("wenquanyi",13,5);
    font.setBold(false);

    QSqlQuery query("",DBConnection::db);;
    query.exec ("select count(*) from switch ");
    query.next();
    int s_num=query.value(0).toInt();       //交换机数量
    int item_height= Listheight/s_num;      //由列表长度和交换机数量得到item高度
//    int item_height= FLASH_LIST_H/s_num;    //由列表长度和交换机数量得到item高度

    flashlist = NULL;
    flashlist = new myFlashList(item_height,s_num,ui->widget_list);

   //初始化交换机列表，同时为每个交换机建立线程
    if(flashlist!=NULL)
    {
//        flashlist->setFixedSize(120,ui->widget_list->height());
        flashlist->setFont(font);

        query.exec ("select name, remark from switch order by ID");
        int swi_next_num=0;
        while(query.next())
        {
            QString str = query.value (0).toString ();
            flashlist->addItem(str);
            SwitchThread *swi_th=new SwitchThread(this,query.value (0).toString ());  //zhushi Shang
            swi_thread_list<<swi_th;
            swi_next_num++;
        }
        insert=new InsertThread(this);
    }

    ui->tabWidget->setFocusPolicy(Qt::NoFocus);
    ui->tabWidget->setDocumentMode(true);

//    int wi = ui->tabWidget->width();
//    int hi = ui->tabWidget->height();

    int wi = QApplication::desktop()->width();
    int hi = QApplication::desktop()->height();


    cpumemplot=new MyPlot();
    cpumemplot->setFixedSize(wi-150,hi-200);
//    portswatch=new PortFlowWatch(ui->widget_show);
    portswatch = new NewPortFlowWatch(ui->tabWidget);
    portswatch->setFixedSize(wi-150,hi-200);

    if(cpumemplot!=NULL){
        ui->tabWidget->clear();
        ui->tabWidget->addTab(cpumemplot,"性能监控");
        ui->tabWidget->addTab(portswatch,"端口流量速率");
    }

    for (int i=0;i<swi_thread_list.size();i++)//
    {
        connect(swi_thread_list.at(i),SIGNAL(sig_finish(QString ,double ,double,double)),cpumemplot,SLOT(updateData(QString,double,double,double)));//cpu ,mem ,延迟更新
        connect(swi_thread_list.at(i),SIGNAL(slg_port(QString,int,double,double)),portswatch,SLOT(slot_updateData(QString,int,double,double)));//端口速率更新
        connect(swi_thread_list.at(i),SIGNAL(sig_portStatus(QString,int ,int)),this,SIGNAL(sig_portStatus(QString,int,int)));//端口状态更新
        connect(swi_thread_list.at(i),SIGNAL(sig_version(QString,QString)),this,SIGNAL(sig_version(QString,QString)));//版本更新
        connect(swi_thread_list.at(i),SIGNAL(sig_interfaceSum(QString,double,double)),cpumemplot,SLOT(updateOther(QString,double,double)));//帶宽更新

        connect(swi_thread_list.at(i),SIGNAL(sig_warning(QString,QString,QString)),this,SLOT(slot_switchWarning(QString,QString,QString)));//告警
        connect(swi_thread_list.at(i),SIGNAL(sig_setNormal(QString)),this,SIGNAL(sig_setNormal(QString)));//交换机恢复信息汇总

        connect(swi_thread_list.at(i),SIGNAL(insert_cpu_mem(QString,double,QString,QString)),insert,SLOT(insert_cpu_men(QString,double,QString,QString)));//性能数据插入数据库
        connect(swi_thread_list.at(i),SIGNAL(insert_portSpeed(QString,double,QString,QString)),insert,SLOT(insert_portSpeed(QString,double,QString,QString)));
        connect(swi_thread_list.at(i),SIGNAL(insert_portStatus(QString,double,QString,QString)),insert,SLOT(insert_portState(QString,double,QString,QString)));
        connect(swi_thread_list.at(i),SIGNAL(sig_cpu_mem_deal(QString,double,QString,QString)),insert,SLOT(sig_cpu_mem_deal(QString,double,QString,QString))); // gaohao 1031 记录数据库变为正常状态
    }

    query.finish();
    query.clear();

    insert->start();
    for (int i=0;i<swi_thread_list.size();i++)
    {
        swi_thread_list.at(i)->start ();
    }
    connect(flashlist,SIGNAL(sig_itemClicked(QString)),cpumemplot,SLOT(setCurrentSwitchNumber(QString)));
    connect(flashlist,SIGNAL(sig_itemClicked(QString)),portswatch,SLOT(slot_setswitchnum(QString)));
}

void MonitorWidget::slot_init_widget()//每次插入删除交换机时更新列表
{
    QFont font("wenquanyi",13,5);
    font.setBold(false);

    QSqlQuery query("",DBConnection::db);;
    query.exec ("select count(*) from switch ");
    query.next();
    int s_num=query.value(0).toInt();

    int item_height= Listheight/s_num;
//    int item_height= FLASH_LIST_H/s_num;

    if(flashlist!=NULL)
    {
        flashlist->clear();
        flashlist->set_item_height(item_height);
    }
    else
    {
        flashlist=new myFlashList(item_height,s_num,ui->widget_list);
    }

    for(int i=0;i<swi_thread_list.size();i++)
    {
       swi_thread_list.at(i)->stop();
       delete swi_thread_list.at(i);//我加的
                                    //Shang,这是我见过最厉害的注释
    }
    insert->terminate();
    swi_thread_list.clear();


    if(flashlist!=NULL)
    {
        flashlist->setFixedSize(120,ui->widget_list->height());
        flashlist->setFont(font);

        query.exec ("select name from switch order by ID");
        int swi_next_num=0;
        while(query.next())
        {
             flashlist->addItem(query.value (0).toString ());
             SwitchThread *swi_th=new SwitchThread(this,query.value (0).toString ());
             swi_thread_list<<swi_th;
             swi_next_num++;
        }
    }

    if(cpumemplot&&portswatch)
    {
        cpumemplot->init_plot();
        portswatch->refresh_port();

        for (int i=0;i<swi_thread_list.size();i++)
        {

          connect (swi_thread_list.at(i),SIGNAL(sig_finish(QString ,double ,double,double)),cpumemplot,SLOT(updateData(QString,double,double,double)));
          connect (swi_thread_list.at(i),SIGNAL(slg_port(QString,int,double,double)),portswatch,SLOT(slot_updateData(QString,int,double,double)));
          connect(swi_thread_list.at(i),SIGNAL(sig_warning(QString,QString,QString)),this,SLOT(slot_switchWarning(QString,QString,QString)));  //qhy 2016.11.12增加一个参数
          connect(swi_thread_list.at(i),SIGNAL(sig_setNormal(QString)),this,SIGNAL(sig_setNormal(QString)));//交换机恢复信息汇总
          connect(swi_thread_list.at(i),SIGNAL(insert_cpu_mem(QString,double,QString,QString)),insert,SLOT(insert_cpu_men(QString,double,QString,QString)));
          //connect(swi_thread_list.at(i),SIGNAL(insert_portSpeed(QString,double,QString,QString)),insert,SLOT(insert_cpu_men(QString,double,QString,QString)));
         // connect(swi_thread_list.at(i),SIGNAL(insert_portStatus(QString,double,QString,QString)),insert,SLOT(insert_cpu_men(QString,double,QString,QString)));
        }
    }
    insert->start();
    for (int i=0;i<swi_thread_list.size();i++)
    {
        swi_thread_list.at(i)->start ();
    }
    query.finish();
    query.clear();
}

void MonitorWidget::slot_switchWarning(QString switchName, QString alarmType, QString value)
{
    emit sig_warningToTop(switchName,alarmType,value);
}

MonitorWidget::~MonitorWidget()
{
    delete ui;
    if(cpumemplot) delete cpumemplot;
    if(portswatch) delete portswatch;
    if(tabWidget) delete tabWidget;
    if(flashlist) delete flashlist;
    for (int i=0;i<swi_thread_list.size();i++)
    {
        delete  swi_thread_list.at(i);
    }
    swi_thread_list.clear();
    if(insert) delete insert;
}
