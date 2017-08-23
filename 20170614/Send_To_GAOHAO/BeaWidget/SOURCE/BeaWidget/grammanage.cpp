#include "grammanage.h"
#include "ui_grammanage.h"
#include "newalarmthreshset.h"
#include "newerrormanage.h"
#include "newshowlogdialog.h"
#include "newshowloghistory.h"
#include "newlistwidgetgram.h"

#include <QSqlQuery>
#include <QDebug>

GramManage::GramManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GramManage)
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"初始化 GramManage"
           <<"\n";
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget_2->setFixedWidth(120);
    ui->widget_2->setFixedHeight(this->height());
    ui->widget_stack->setFixedSize(this->width()-120,this->height());
    ui->stack_widget->setFixedSize(this->width()-120,this->height());
    optionList = NULL;
    logDialog = NULL;
    alarmthreshset = NULL;
    errorManage = NULL;
    logHistory = NULL;
    initOptionView();
}

void GramManage::initOptionView()
{
    if(!optionList)
    {
        optionList = new NewListWidgetGram(ui->widget_2);
    }

    if(!alarmthreshset)
    {
        alarmthreshset = new NewAlarmThreshSet(ui->widget_stack);
    }

    if(!errorManage)
    {
        errorManage = new NewErrorManage(ui->widget_stack);
    }

    if(!logDialog)
    {
        logDialog = new NewShowLogDialog(ui->widget_stack);
    }

    if(!logHistory)
    {
        logHistory = new NewShowLogHistory(ui->widget_stack);
    }

    ui->stack_widget->insertWidget(0,alarmthreshset);
    ui->stack_widget->insertWidget(1,errorManage);
    ui->stack_widget->insertWidget(2,logDialog);
    ui->stack_widget->insertWidget(3,logHistory);

    ui->stack_widget->setCurrentWidget(alarmthreshset);

    connect(optionList,SIGNAL(turnpage(int)),this,SLOT(slot_indexchange(int)));
    connect(this,SIGNAL(signal_indexchange(int)),ui->stack_widget,SLOT(setCurrentIndex(int)));
}

void GramManage::slot_indexchange(int index)
{
    emit signal_indexchange(index);
    qDebug()<<"------------"<<ui->stack_widget->widget(index)->objectName()<<"++++++++++"<<index;
}

GramManage::~GramManage()
{
    delete ui;
    if(logDialog)delete logDialog;
    if(errorManage)delete errorManage;
    //if(errorDeal)delete errorDeal;
    if(alarmthreshset)delete alarmthreshset;
    if(main_layout)delete main_layout;
    if(logHistory)delete logHistory;

}
