#include "search_performance.h"
#include "ui_search_performance.h"
#include <qheaderview.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QColor>
#include <QCalendarWidget>
#include <QDate>
#include <QDialog>
#include <QString>
#include <QTextCharFormat>
#include <QCursor>
#include <QLocale>
#include <QPalette>
#include <QSignalMapper>
#include <QSqlQuery>
#include<QApplication>
#include<QDesktopWidget>
#include"connection.h"
#include"insertthread.h"
Search_performance::Search_performance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_performance)
{
    ui->setupUi(this);
    flag=0;
    QHBoxLayout *searchCon1 = new QHBoxLayout();
    QHBoxLayout *searchCon2 = new QHBoxLayout();

    QPalette pl_title;
    pl_title.setColor(QPalette::WindowText,Qt::white);


    switchName = new LabelComBox();
    QSqlQuery sqlquery("",DBConnection::db);
    sqlquery.exec("select  name from switch");
    switchName->addItem("");
    while(sqlquery.next())
    {
        switchName->addItem(sqlquery.value(0).toString());
    }
    switchName->setLabel("交换机名:");


    alarmClass = new LabelComBox();    
    alarmClass->addItem("");
    alarmClass->addItem("CPU温度");
    //alarmClass->addItem("内存");
    alarmClass->addItem("端口进速率");
    alarmClass->addItem("端口出速率");
    alarmClass->addItem("端口状态");
    alarmClass->setLabel("性能项");

    state=new LabelComBox();
    state->addItem("");
    state->addItem("正常");
    state->addItem("超限");
    state->addItem("UP");
    state->addItem("DOWN");
    state->setLabel("状态");

    port=new LabelComBox();
    port->setLabel("端口");
    port->addItem("");
    for(int i=1;i<=60;i++)
    {
        port->addItem(QString::number(i));
    }
    port->setEnabled(false);
    starttime = new DateEdit();
    starttime->setLabel("开始时间 :");
    endtime = new DateEdit();
    endtime->setLabel("结束时间 :");

    label5 = new QLabel(tr("~"));
    label5->setStyleSheet("border:none"
                          "color:white;");

    search = new commonButton();
    search->setText("查询");
    search->setFocusPolicy( Qt::NoFocus );
    search->setFixedSize(120,30);

    clear = new commonButton();
    clear->setText("清空数据库");
    clear->setFocusPolicy( Qt::NoFocus );
    clear->setFixedSize(120,30);

    clearTime = new commonButton();
    clearTime->setText("清空时间");
    clearTime->setFocusPolicy( Qt::NoFocus );
    clearTime->setFixedSize(120,30);

    searchCon1->addWidget(switchName);
    searchCon1->addSpacing(14);
    searchCon1->addWidget(alarmClass);
    searchCon1->addStretch(2);
    searchCon1->addWidget(state);
    searchCon1->addStretch(1);
     searchCon1->addWidget(port);


    searchCon2->addWidget(starttime);
    searchCon2->addWidget(label5);
    searchCon2->addWidget(endtime);
    searchCon2->addStretch(2);
   searchCon2->addWidget(clearTime);
   searchCon2->addStretch(1);
    searchCon2->addWidget(search);
    searchCon2->addStretch(1);
    searchCon2->addWidget(clear);

    searchCon1->setContentsMargins(0,0,0,0);
    searchCon2->setContentsMargins(0,0,0,0);

    main_layout  = new QVBoxLayout();
    main_layout->addLayout(searchCon1);
    main_layout->addLayout(searchCon2);


    label5->setPalette(pl_title);

    this->setLayout(main_layout);
   sqlquery.finish();
   sqlquery.clear();
   connect(search,SIGNAL(click()),this,SLOT(slot_search()));
   connect(clear,SIGNAL(click()),this,SLOT(slot_clear()));
   connect(clearTime,SIGNAL(click()),this,SLOT(slot_clearTime()));
   connect(alarmClass,SIGNAL(indexChanged(QString)),this,SLOT(slot_setPort(QString)));

}
void Search_performance::slot_search()
{
    QString date_st=starttime->text();
    QString date_ed=endtime->text();

    QString swi_name=switchName->text();
    QString type=alarmClass->text();
    QString performanceState=state->text();
    QString currentPort=port->text();
    emit signal_search(swi_name,type,date_st,date_ed,performanceState,currentPort);
}

void Search_performance::slot_clear()
{
    emit signal_clear();
}

void Search_performance::slot_clearTime()
{
    starttime->m_edit->clear();
    endtime->m_edit->clear();
}

void Search_performance::slot_setPort(QString text)
{
    if(text=="端口进速率"||text=="端口出速率")
         port->setEnabled(true);
   else
        {
        port->setEnabled(false);
        port->setIndex(0);
    }
}

Search_performance::~Search_performance()
{

    if(starttime)delete starttime;
    if(endtime)delete endtime;

    if(label5)delete label5;
    if(search)delete search;
    if(switchName)delete switchName;
    if(alarmClass)delete alarmClass;
    if(main_layout)delete main_layout;
    delete ui;

}
