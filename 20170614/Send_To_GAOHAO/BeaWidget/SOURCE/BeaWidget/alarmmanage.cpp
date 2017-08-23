#include "alarmmanage.h"
#include "ui_alarmmanage.h"
#include "alarmtableview.h"
#include "barchart.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QHBoxLayout>
AlarmManage::AlarmManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmManage)
{
    ui->setupUi(this);
    QDateTime time;
    time = QDateTime::currentDateTime();
//    QString ss = time.toString(Qt::ISODate);
    QSqlQuery query;
//    query.exec("insert into alarm values(2, '一般','2舱B','192.168.0.34','电压过低','"+ss+"','"+ss+"','否')");
    query.exec ("select distinct 告警类型 from alarm where 交换机位置 = '2舱B' and 开始时间 >'2014-07-24T20:59:30' and 最后发生时间<'2014-07-24T22:31:28'");

    QSqlQuery query1;
    query1.exec("delete from alarmquery");
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString alarmclass=query.value (0).toString ();
        query1.exec ("select count(*) from alarm where 告警类型='"+alarmclass+"' and 交换机位置 = '2舱B' and 开始时间 >'2014-07-24T20:59:30' and 最后发生时间<'2014-07-24T22:31:28'");
        query1.next ();
        int alarmtimes=query1.value (0).toInt ();
        query1.exec ("insert into alarmquery values("+QString::number (alarmtimes)+",'"+alarmclass+"')");
    }
    int n=12;  //交换机数量
    QFont font("wenquanyi",13,5);
    font.setBold(false);

    flashlist=new myFlashList(this);

    if(flashlist!=NULL){
        flashlist->setStyleSheet("background:rgb(54,54,54);");
        flashlist->setFixedSize(100,420);
        flashlist->setFont(font);
        QString address;
        for(int i=0;i<n;i++)
        {
            query.exec ("select 位置 from switch where 序号 ="+QString::number (i+1));
            query.next ();
            address=query.value (0).toString ();
            flashlist->addItem(address);
        }
    }
//     connect (flashlist,SIGNAL(sig_itemClicked(int)),cpumemplot,SLOT(setCurrentSwitchNumber(int)));
    AlarmTableView *alarmtableview=new AlarmTableView();
    alarmtableview->setFixedSize (800,200);
    alarmtableview->slot_query();
    BarChart *barchart=new BarChart(this);
    barchart->setFixedWidth (400);
    ui->verticalLayout->setMargin (1);
    ui->verticalLayout->addWidget (barchart,0,Qt::AlignRight);
    ui->verticalLayout->addWidget (alarmtableview,0,Qt::AlignRight);
    //barchart->customPlot->setFixedSize (400,230);
   // barchart->slot_reLoadData ();
    QHBoxLayout *hboxlayout=new QHBoxLayout(this);
    hboxlayout->addWidget (flashlist,0,Qt::AlignVCenter);
    hboxlayout->addSpacing (10);
    hboxlayout->addWidget (ui->verticalLayoutWidget);
    setLayout (hboxlayout);
}

AlarmManage::~AlarmManage()
{
    delete ui;
}
