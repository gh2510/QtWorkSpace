#include "mainview.h"
#include "ui_mainview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "logindialog.h"
//#include "newlistwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QSplashScreen>

//Shang 2017.02.17
#include <QDebug>

MainView::MainView(QWidget *parent, QSplashScreen *splash) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignBottom;
    splash->showMessage(QObject::tr("初始化设备监控......"),topRight, Qt::white);

    ui->setupUi(this);
    this->setFixedSize(parent->width(),parent->height());
    ui->widget_listButton->setFixedSize(120,this->height());
    ui->widget_stack->setFixedSize(this->width()-120,this->height());
    st = NULL;
    ah = NULL;
    switchmanage = NULL;
    sc = NULL;
    cdg = NULL;
    optionList=NULL;

    splash->showMessage(QObject::tr("初始化拓扑视图......"),topRight, Qt::white);
    createsSwitcher_Topo();
    splash->showMessage(QObject::tr("加载拓扑视图完成......"),topRight, Qt::white);
    splash->showMessage(QObject::tr("初始化交换机管理视图......"),topRight, Qt::white);
    createNewSwitchManage();
    splash->showMessage(QObject::tr("加载交换机管理视图完成......"),topRight, Qt::white);

    if(optionList==NULL)
    {
        //Shang
        optionList = new NewListwidget(ui->widget_listButton);
    }
    connect(optionList,SIGNAL(turnpage(int)),this,SLOT(slot_indexchange(int)));
    optionList->setFirstPressed(0);
    cdg=NULL;
}

//创建拓扑视图界面
void MainView::createsSwitcher_Topo()
{
    if(!st)
    {
        st = new switcher_topo(ui->widget_stack);
        ui->stack_widget->addWidget(st);
    }
}

//创建告警查询界面
void MainView::createNewAlarmHistory()
{
    if(!ah)
    {
        ah = new NewAlarmHistory(ui->widget_stack);
        ui->stack_widget->addWidget(ah);
    }
}

//创建交换机管理界面
void MainView::createNewSwitchManage()
{
    if(!switchmanage)
    {
        switchmanage = new NewSwitchManage(ui->widget_stack);
        ui->stack_widget->addWidget(switchmanage);
    }
}

//创建配置管理界面
void MainView::createSwitch_Conf()
{
    if(!sc)
    {
        sc = new switch_conf(ui->widget_stack);
        ui->stack_widget->addWidget(sc);
    }
}

void MainView::initOptionView()
{
}

void MainView::slot_indexchange(int index)
{
    if(index == 3)
    {
        if(cdg==NULL)
        {
            cdg = new NewCapturDialog(this);
        }
        cdg->move((QApplication::desktop()->width()-cdg->width())/2,
                      (QApplication::desktop()->height()-cdg->height())/2);
        cdg->exec();
        return;
    }

    QWidget *widget=NULL;
    switch(index)
    {
    case 0:
        widget = st;
        break;
    case 1:
        createNewAlarmHistory();
        widget = ah;
        break;
    case 2:
        createNewSwitchManage();
        widget = switchmanage;
        break;
    case 4:
        if(userLevel==0)// 如果是管理员    开机时自动将所有页面都创建好，以便账户切换 yangmeng 161022
        {
            createSwitch_Conf();
            widget = sc;
        }
        break;
    }

    ui->stack_widget->setCurrentWidget(widget);
}

MainView::~MainView()
{
    delete ui;
    if(st)delete st;
    if(ah)delete ah;
    if(sc)delete sc;
    if(switchmanage)delete switchmanage;
    if(cdg)
    {
        delete cdg;
        cdg=NULL;
    }
}

//改变用户角色 yangmeng 161022
void MainView::changeUser()
{
    if(userLevel == 0)  //管理员
    {
        if(!sc)
        {
            createSwitch_Conf();
        }
        else
        {
            ui->stack_widget->addWidget(sc);
        }
    }
    else                     //普通用户
    {
        if(sc)
        {
            ui->stack_widget->removeWidget(sc);     //屏蔽交换机配置页面
            sc->hide();
        }

    }
    optionList->changeUser();
    optionList->setFirstPressed(0);

}
