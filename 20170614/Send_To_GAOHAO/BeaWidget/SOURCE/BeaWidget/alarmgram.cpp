#include "alarmgram.h"
#include <QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
 #include"connection.h"
AlarmGram::AlarmGram(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(QApplication::desktop()->width()*5/6,QApplication::desktop()->height()*5/6);
    initWidget();
}

AlarmGram::~AlarmGram()
{
    if(switch_lc)delete switch_lc;
    if(starttime)delete starttime;
    if(endtime)delete endtime;
    if(alarmlevel)delete alarmlevel;
    if(alarmtype)delete alarmtype;
    if(search)delete search;
    if(exportgram)delete exportgram;
    if(cancel)delete cancel;
    if(toplayout)delete toplayout;
    if(centerlayout)delete centerlayout;
    if(bottomlayout)delete bottomlayout;
    if(mainlayout)delete mainlayout;
    if(alarminfo)delete alarminfo;
    if(scroll)delete scroll;
}
void AlarmGram::initWidget()
{
    QSqlQuery query("",DBConnection::db);;
    QString location;

    switch_lc=new LabelComBox();
    switch_lc->setLabel("选择设备");
    switch_lc->addItem("All Switch");
    query.exec ("select location from switch order by ID");
    while( query.next ())
    {
     location=query.value (0).toString ();
     switch_lc->addItem(location);
    }
    query.finish();
    switch_lc->setFixedSize(300,30);

    alarmstate_lc=new LabelComBox();
    alarmstate_lc->setLabel("设备状态");
    alarmstate_lc->addItem("所有状态");
    alarmstate_lc->addItem("未解决");
    alarmstate_lc->addItem("已解决");
    alarmstate_lc->setFixedSize(300,30);

    starttime=new DateEdit();
    starttime->setLabel("starttime");
    starttime->setFixedSize(300,30);

    endtime=new DateEdit();
    endtime->setLabel("endtime");
    endtime->setFixedSize(300,30);

    alarmlevel=new LabelComBox();
    alarmlevel->setLabel("告警级别");
    alarmlevel->addItem("All Level");
    alarmlevel->addItem("level1");
    alarmlevel->addItem("level2");
    alarmlevel->addItem("level3");
    alarmlevel->addItem("level4");
    alarmlevel->setFixedSize(300,30);

    alarmtype=new LabelComBox();
    alarmtype->setLabel("告警类型");
    alarmtype->addItem("电压过高");
    alarmtype->addItem("温度过高");
    alarmtype->addItem("CPU使用率过高");
    alarmtype->addItem("内存使用率过高");
    alarmtype->addItem("硬盘空间不足");
    alarmtype->addItem("网络不通");
    alarmtype->addItem("存在网络风暴危险");
    alarmtype->addItem("丢包率过高");
    alarmtype->addItem("时延较大");
    alarmtype->addItem("包错误率过高");
    alarmtype->setFixedSize(300,30);

    search=new commonButton();
    search->setText("查询");
    search->setFixedSize(100,30);

    exportgram=new  commonButton();
    exportgram->setText("导出");
    exportgram->setFixedSize(100,30);

    cancel=new commonButton();
    cancel->setText("取消");
    cancel->setFixedSize(100,30);



    toplayout=new QHBoxLayout();
    toplayout->addWidget(switch_lc,0,Qt::AlignLeft|Qt::AlignVCenter);
    toplayout->addStretch(1);
    toplayout->addWidget(alarmstate_lc,0,Qt::AlignVCenter);
    toplayout->addStretch(2);
    toplayout->addWidget(search,0,Qt::AlignVCenter);
    toplayout->addStretch(1);
    toplayout->setContentsMargins(5,3,5,0);

    centerlayout=new QHBoxLayout();
    centerlayout->addWidget(starttime,0,Qt::AlignLeft|Qt::AlignVCenter);
      centerlayout->addStretch(1);
    centerlayout->addWidget(endtime,0,Qt::AlignVCenter);
      centerlayout->addStretch(2);
    centerlayout->addWidget(exportgram,0,Qt::AlignVCenter);
      centerlayout->addStretch(1);
    centerlayout->setContentsMargins(5,3,5,0);

    bottomlayout=new QHBoxLayout();
    bottomlayout->addWidget(alarmlevel,0,Qt::AlignLeft|Qt::AlignVCenter);
      bottomlayout->addStretch(1);
    bottomlayout->addWidget(alarmtype,0,Qt::AlignVCenter);
      bottomlayout->addStretch(2);
    bottomlayout->addWidget(cancel,0,Qt::AlignVCenter);
      bottomlayout->addStretch(1);
    bottomlayout->setContentsMargins(5,3,5,0);

    alarminfo=new AlarmGramInfo();
    alarminfo->setFixedSize(700,1200);

    scroll=new QScrollArea();
    scroll->setFixedHeight(390);
    scroll->setWidget(alarminfo);
    scroll->setAlignment(Qt::AlignHCenter);
    scroll->setWidgetResizable(true);

    mainlayout=new QVBoxLayout();
    mainlayout->addLayout(toplayout);
    mainlayout->addLayout(centerlayout);
    mainlayout->addLayout(bottomlayout);
    mainlayout->addSpacing(8);
    mainlayout->addWidget(scroll);
    mainlayout->addStretch();
    mainlayout->setContentsMargins(5,5,5,0);

    setLayout(mainlayout);

    connect(search,SIGNAL(click()),this,SLOT(slot_searchclick()));
    connect(exportgram,SIGNAL(click()),this,SIGNAL(signal_exportclick()));
    connect(cancel,SIGNAL(click()),this,SLOT(slot_cancel()));

}
void AlarmGram::slot_searchclick()
{
    emit signal_searchpram(switch_lc->text(),alarmstate_lc->text()\
                           ,starttime->text(),endtime->text()\
                           ,alarmlevel->text(),alarmtype->text());

}
void AlarmGram::slot_cancel()
{
    switch_lc->clear();
    alarmstate_lc->clear();
    starttime->clear();
    endtime->clear();
    alarmlevel->clear();
    alarmtype->clear();
}
