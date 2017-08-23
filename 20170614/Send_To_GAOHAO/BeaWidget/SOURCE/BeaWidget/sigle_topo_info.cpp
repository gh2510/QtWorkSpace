#include "sigle_topo_info.h"
#include "ui_sigle_topo_info.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QDebug>
#include "showswitch.h"
#include "connection.h"
sigle_topo_info::sigle_topo_info(QWidget *parent) :
    QWidget(parent),ui(new Ui::sigle_topo_info)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget_titleshow->setFixedWidth(this->width()*9.3/10);//这一行调整大小后，可以将右边的空间留出
    ui->widget_titleshow->setFixedHeight(this->height()*2/10);
    ui->tb_info->setFixedWidth(ui->widget_titleshow->width());
//    ui->tb_info->setMinimumHeight(this->height()*3.5/10);

    ui->widget_switch_2->setFixedWidth(ui->tb_info->width());
    ui->widget_switch_2->setFixedHeight(220);
    ui->widget_switchstateview->setMinimumWidth(ui->widget_switch_2->width());
    ui->widget_switchstateview->setMinimumHeight(ui->widget_switch_2->height()*9.5/10);
    ui->widget_char->setFixedHeight(this->height()*0.15/10);
    tbInfoModel=NULL;
    m_name=NULL;
    m_location=NULL;
    m_leIP=NULL;
    m_lestate=NULL;
    tb_info=NULL;
    ssv=NULL;
    loopv=NULL;
    info_button=NULL;
    dialog = new SwitchInfoDialog(this);

    initWidget();
}

void sigle_topo_info::slot_portStatus(QString name,int index ,int state)//根据发过来的交换机端口状态信号更新单个交换机信息框
{
    if(!portsState.contains(name))
    {
        portsState[name]=new int [60];
        for(int j=0;j<60;j++)
            portsState[name][j]=2;
    }
    portsState[name][index]=state;
    //更新交换机状态图
    if(portsState.contains(switchName))
    {
        for(int i=0;i<60;i++)
        {
          ssv->change_port_state(i,portsState[switchName][i]);
        }
    }
    //更新交换机链接设备信息表
    if(name==switchName)
    {
        if(state==1)
             dialog->switchTableModel->setItem(index,2,new QStandardItem("在线"));
        if(state==2)
            //dialog->switchTableModel->setItem(index,2,new QStandardItem("断开"));
            dialog->switchTableModel->setItem(index,2,new QStandardItem("离线"));     //yangmeng 161026 按照要求修改
    }
}

 void sigle_topo_info::slot_version(QString name, QString version)
 {
     QString temp= version.replace("JARIOS Software,","");
     temp=temp.replace("JariOS Software,","");
     versionMap[name] = temp;       //yangmeng 161026 版本信息缓存，点选后快速显示

    if(switchName==name)
    {
//       m_lestate->setText(temp);  //Shang debug problem
        ui->m_lestate->setText(temp);
    }
 }


void sigle_topo_info::initWidget()
{

    if(tbInfoModel!=NULL)
        delete tbInfoModel;
    tbInfoModel=new myStandardItemModel();
    tbInfoModel->setHorizontalHeaderItem(0,new QStandardItem(tr("告警类型")));
    // tbInfoModel->setHorizontalHeaderItem(1,new QStandardItem(tr("告警等级")));
    tbInfoModel->setHorizontalHeaderItem(1,new QStandardItem(tr("开始时间")));

    if(tb_info!=NULL)
        delete tb_info;
    //    tb_info=new QTableView();
    ui->tb_info->setModel(tbInfoModel);
    ui->tb_info->verticalHeader()->hide();
    ui->tb_info->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tb_info->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tb_info->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->info_button->setText("查看详细信息");

    if(ssv!=NULL)
        delete ssv;
    ssv = new SwitchStateView(ui->widget_switchstateview);

    /* 根据沟通隐藏告警信息的显示效果
    if(loopv!=NULL)
     delete loopv;
    loopv=new LoopView();

    loopv->setFixedWidth(QApplication::desktop()->width()*27/100);//280
    loopv->setFixedHeight(QApplication::desktop()->height()/5);//200
    font=m_location->font();

    loopv->setFont(font);
    */
    connect(ui->info_button,SIGNAL(clicked()),this,SLOT(slot_showInfo()));
    slot_switchSelected("H1","60");

    initTableWidth();
}

void sigle_topo_info::initTableWidth()
{
    ui->tb_info->setColumnWidth(0,this->width()/2-2);
    ui->tb_info->setColumnWidth(1,this->width()/2-2);
}

sigle_topo_info::~sigle_topo_info()
{
    if(tbInfoModel) delete tbInfoModel;
    if(m_name) delete m_name;
    if(m_location) delete m_location;
    if(m_leIP)delete m_leIP;
    if(m_lestate)delete m_lestate;
    if(tb_info) delete tb_info;
    if(info_button) delete info_button;
    if(dialog) delete dialog;
}

//void sigle_topo_info::paintEvent(QPaintEvent * e)
//{
//    QPainter * painter=new QPainter(this);
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(5,5,this->width()-10,this->height()-10);
//    painter->setRenderHint(QPainter::Antialiasing,true);
//    painter->fillPath(path,QBrush(QColor(75,75,75)));
//   QColor color(137,137,130,178);

//    for(int i=0;i<3;i++)
//    {
//        QPainterPath patht;
//        patht.setFillRule(Qt::WindingFill);
//        path.addRect(5-i,5-i,this->width()-(5-i)*2,this->height()-(5-i)*2);
//        color.setAlpha((200-qSqrt(i)*50));
//        painter->setPen(color);
//        painter->drawPath(path);
//    }
//    delete painter;
//    QWidget::paintEvent(e);
//}

void sigle_topo_info::slot_showInfo()
{

    QStringList list;
    for(int j=0;j<switchType;j++)
        //list.append("断开");
        list.append("离线");      //yangmeng 161026 按照要求修改
     for(int i=0;i<switchType;i++)
     {
          if(ssv->pix_list.at(i)->pixmap()==ssv->switch_pix_green)
          {
               list.at(i)==" 在线";
          }

     }
     //dialog->setSwitch(m_name->text().trimmed());
     dialog->setList(list);
     dialog->init_table();
     dialog->move((QApplication::desktop()->width()-dialog->width())/2,
                  (QApplication::desktop()->height()-dialog->height())/2);
     dialog->exec();


 }

void  sigle_topo_info::slot_sig_alarm(QString switchname)    //realtime flush alarm state
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"switchname:"<<switchname<<" switchName.right(2):"<<switchName.right(2)
           <<"\n";
    int itemCount=0;
    if (switchname != switchName.right(2))
        return;
    QSqlQuery query("",DBConnection::db);
    //dialog->setSwitch(query.value(0).toString(),query.value(1).toString(),query.value(3).toString());
    query.exec(QString("select a.alarmtype,a.starttime from alarmcurrent a   where a.name='%1' and a.isdeal='否' order by a.name, a.alarmtype")
               .arg(switchname.right(2)));
    tbInfoModel->clear();
    tbInfoModel->setHorizontalHeaderItem(0,new QStandardItem(tr("告警类型")));
    tbInfoModel->setHorizontalHeaderItem(1,new QStandardItem(tr("开始时间")));

    while(query.next())
    {
        tbInfoModel->setItem(itemCount,0,new QStandardItem(query.value(0).toString()));
        tbInfoModel->setItem(itemCount,1,new QStandardItem(query.value(1).toString()));
        itemCount++;
    }
    query.finish();
    query.clear();
    ui->tb_info->setModel(tbInfoModel);

    initTableWidth();
}

 void  sigle_topo_info::slot_switchSelected(QString switchid,QString type)//单击交换机图标触发的事件
 {
     QSqlQuery query("",DBConnection::db);
     query.exec(QString("select  c.description,c.location,c.IP,c.remark from switch c where c.name='%1'").arg(switchid.right(2)));
     query.next();
     int itemCount=0;
     ui->m_name->setText(query.value(0).toString());
     ui->m_location->setText(query.value(1).toString());
     ui->m_leIP->setText(query.value(2).toString());
     //m_lestate->setText("");
     if(versionMap.contains(switchid))
     {
        ui->m_lestate->setText(versionMap[switchid]);      //yangmeng 161026 显示缓存的版本信息
     }
     else
     {
        ui->m_lestate->setText("正在获取");                 //yangmeng 161026 版本信息
     }
     //m_lestate->setText(query.value(3).toString());
     dialog->setSwitch(query.value(0).toString(),query.value(1).toString(),query.value(3).toString());
     query.exec(QString("select a.alarmtype,a.starttime from alarmcurrent a   where a.name='%1' and a.isdeal='否' order by a.name, a.alarmtype")
                .arg(switchid.right(2)));
     tbInfoModel->clear();
     tbInfoModel->setHorizontalHeaderItem(0,new QStandardItem(tr("告警类型"))); 
     tbInfoModel->setHorizontalHeaderItem(1,new QStandardItem(tr("开始时间")));

    while(query.next())
    {
        tbInfoModel->setItem(itemCount,0,new QStandardItem(query.value(0).toString()));    
        tbInfoModel->setItem(itemCount,1,new QStandardItem(query.value(1).toString()));

        itemCount++;
    }
   query.finish();
   query.clear();
   ui->tb_info->setModel(tbInfoModel);

   ssv->setTitle(switchid);
   bool ok;
   switchType=type.toInt(&ok,10);
   switchName=switchid;
   ssv->setSwitchType(switchType);
   for(int i=0;i<60;i++)
   {
//       for(int i=0;i<60;i++)      //yangmeng 161028 优化
         ssv->change_port_state(i,2);
   }
    initTableWidth();
 }
