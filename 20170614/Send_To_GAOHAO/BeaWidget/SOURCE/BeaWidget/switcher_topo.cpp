#include "switcher_topo.h"
#include "ui_switcher_topo.h"
#include "mainwindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

#include <QFile>                 //yangmeng 161026 日志记录核心交换机端口变化
#include <QTextStream>
#include <QDate>
#include <QMessageBox>
#include <QDebug>

switcher_topo::switcher_topo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::switcher_topo)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());

    ui->widget->setFixedSize(this->width(),this->height());
    ui->widget_2->setFixedWidth(this->width()*6/10);
    ui->widget_3->setFixedWidth(ui->widget_2->width());
    ui->widget_topview->setFixedWidth(ui->widget_3->width());
    ui->widget_topview->setMinimumHeight(this->height()-230);

    ui->widget_switch->setMinimumWidth(ui->widget_topview->width()-10);
    ui->widget_switch->setFixedHeight(220);

    ui->widget_switch_page_1->setFixedWidth(ui->widget_switch->width()/2);
    ui->widget_switch_page_1->setFixedHeight(ui->widget_switch->height());
    ui->widget_switchstate_1->setMinimumWidth(ui->widget_switch->width()/2);
    ui->widget_switchstate_1->setMinimumHeight(ui->widget_switch->height()*9.5/10);

    ui->widget_switch_page_2->setFixedWidth(ui->widget_switch->width()/2);
    ui->widget_switch_page_2->setFixedHeight(ui->widget_switch->height());
    ui->widget_switchstate_2->setMinimumWidth(ui->widget_switch->width()/2);
    ui->widget_switchstate_2->setMinimumHeight(ui->widget_switch->height()*9.5/10);

    ui->widget_single_top->setFixedWidth((ui->widget->width()-ui->widget_2->width())*9.5/10);
    ui->widget_single_top->setFixedHeight(this->height());

    alarmtableview = new sigle_topo_info(ui->widget_single_top);
    topview = new TopView(ui->widget_topview);
    topview->slot_ChangePixItem (3,2);                          //switch 3 is down
    m_ssv_sw2 = new SwitchStateView(ui->widget_switchstate_1);
    m_ssv_sw2->setTitle("H1");
    m_ssv_sw2->setSwitchType(60);
    m_ssv_sw3 = new SwitchStateView(ui->widget_switchstate_2);
    m_ssv_sw3->setTitle("H2");
    m_ssv_sw3->setSwitchType(60);

    connect(topview,SIGNAL(signal_switchSelected(QString,QString)),
            alarmtableview,SLOT(slot_switchSelected(QString,QString)));
}

QString numToState(int num)
{
    switch(num)
    {
    case 0:
        return QObject::tr("测试");
    case 1:
        return QObject::tr("连通");
    case 2:
        return QObject::tr("断开");
    case 3:
        return QObject::tr("告警");
    }
}

void switcher_topo::slot_portStatus(QString name,int index ,int state)//根据发过来的交换机端口状态信号更新核心交换机端口状态图
{
   if(!portsState.contains(name))
   {
       portsState[name]=new int [60];
       for(int j=0;j<60;j++)
           portsState[name][j]=-1;      //默认状态为-1，下面识别为-1时表示首次开机，不计入日志 yangmeng 161026
   }

   if((portsState[name][index]!=state) &&(portsState[name][index]!=-1) )     //yangmeng 161026 状态变化时写入日志
   {
         if(name == "B2" )
            qDebug()<<"ErrorInfo" << name << "," << state;
       QString newRecord ;

      //写入日志文件，qhy 2016.11.29
       MainWindow::setLogfileName();
       QFile file(MainWindow::logFileName);

       if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
       {
           QMessageBox::information(0,tr("错误10"),tr("日志文件打开失败！"),QMessageBox::Ok);
       }
       QTextStream out(&file);
       QString temp;

       //newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [端口状态]")+tr("交换机")+name+tr("的端口")+temp.setNum(index)+tr("状态由'")+temp1.setNum(portsState[name][index])+tr("'变为'")+temp2.setNum(state)+tr("'");
       newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [端口状态]")+tr("交换机")+name+tr("的端口")+temp.setNum(index+1)+tr("状态由'")+numToState(portsState[name][index])+tr("'变为'")+numToState(state)+tr("'");
       out<<newRecord<<endl;
       file.close();

       //yangmeng 161026 日志实时更新
       emit signal_addRecord(newRecord);
   }

   portsState[name][index]=state;

   if(portsState.contains("H1"))
   {
//       for(int i=0;i<60;i++)
//         m_ssv_sw2->change_port_state(i,portsState["H1"][i]);       
       m_ssv_sw2->change_port_state(index,portsState["H1"][index]);     //yangmeng 161026 减少界面刷新
   }
   if(portsState.contains("H2"))
   {
//       for(int i=0;i<60;i++)
//         m_ssv_sw3->change_port_state(i,portsState["H2"][i]);
       m_ssv_sw3->change_port_state(index,portsState["H2"][index]);     //yangmeng 161026 减少界面刷新
   }

}

switcher_topo::~switcher_topo()
{
    QMap<QString,int*>::iterator it;
    for(it=portsState.begin();it!=portsState.end();++it)
    {
        int * tt=it.value();
        delete [] tt;
    }

//   if(sv_h_layout)delete sv_h_layout; //Shang
//   if(left_layout)delete left_layout;
//   if(topinfo_layout)delete topinfo_layout;
  // delete m_ssv_sw1;
   delete m_ssv_sw2;
   delete m_ssv_sw3;
  // delete m_ssv_sw4;
   delete ui;
}
