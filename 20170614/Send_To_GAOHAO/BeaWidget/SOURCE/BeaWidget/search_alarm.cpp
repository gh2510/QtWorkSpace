#include "search_alarm.h"

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

search_alarm::search_alarm(QWidget *parent) :
    QWidget(parent)
{
   //setFixedHeight(QApplication::desktop()->height()*1/6);
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
    sqlquery.exec("select  alarmtype from alarmquery");
    while(sqlquery.next())
    {
        alarmClass->addItem(sqlquery.value(0).toString());
    }
    alarmClass->setLabel("告警类型");

    isConfirmed= new LabelComBox(this);
    isConfirmed->addItem ("");
    isConfirmed->addItem ("是");
    isConfirmed->addItem ("否");
    isConfirmed->setLabel("是否处理:");

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
    search->setFixedSize(110,30);

    clearTime = new commonButton();
    clearTime->setText("清空时间");
    clearTime->setFocusPolicy( Qt::NoFocus );
    clearTime->setFixedSize(110,30);

    clearData = new commonButton();
    clearData->setText("清空数据");
    clearData->setFocusPolicy( Qt::NoFocus );
    clearData->setFixedSize(110,30);

    searchCon1->addWidget(switchName);
    searchCon1->addSpacing(14);
    searchCon1->addWidget(alarmClass);
    searchCon1->addStretch(1);
    searchCon1->addWidget(isConfirmed);
    searchCon1->addStretch(1);
    searchCon1->addWidget(clearData);
    searchCon1->addStretch(1);

    searchCon2->addWidget(starttime);
    searchCon2->addWidget(label5);   
    searchCon2->addWidget(endtime);
    searchCon2->addStretch(2);
    searchCon2->addWidget(clearTime);
    searchCon2->addStretch(1);
    searchCon2->addWidget(search);
    searchCon2->addStretch(1);

//    searchCon2->addWidget(clearData);
//    searchCon2->addStretch(1);
    //searchCon2->addWidget(clear);
    //searchCon2->addStretch(1);

    searchCon1->setContentsMargins(0,0,0,0);
    searchCon2->setContentsMargins(0,0,0,0);

    main_layout  = new QVBoxLayout();
    main_layout->addLayout(searchCon1);
    main_layout->addLayout(searchCon2);
    //main_layout->addWidget(clear);

    label5->setPalette(pl_title);

    this->setLayout(main_layout);
   sqlquery.finish();
   sqlquery.clear();
    connect(search,SIGNAL(click()),this,SLOT(slot_search()));
    connect(clearTime,SIGNAL(click()),this,SLOT(slot_clearTime()));
    connect(clearData,SIGNAL(click()),this,SLOT(slot_clearData()));

}

//点击查询按钮后发出查询信号
void search_alarm::slot_search()
{
    QString date_st=starttime->text();
    QString date_ed=endtime->text();
    QString iscom=isConfirmed->text();
    QString swi_name=switchName->text();
    QString alarm=alarmClass->text();


    emit signal_search(swi_name,alarm,iscom,date_st,date_ed);
}

//清空时间按钮的操作
void search_alarm::slot_clearTime()
{
    starttime->m_edit->clear();
    endtime->m_edit->clear();

}

//清空数据，逻辑待增加
void search_alarm::slot_clearData()
{
//    QSqlQuery query("",db_sqlite);
//    query.exec("delete  from alarm");
}



search_alarm::~search_alarm()
{

    if(starttime)delete starttime;
    if(endtime)delete endtime;
    if(isConfirmed)delete  isConfirmed;
    if(label5)delete label5;
    if(search)delete search;
    if(switchName)delete switchName;
    if(alarmClass)delete alarmClass;
    if(main_layout)delete main_layout;

}


