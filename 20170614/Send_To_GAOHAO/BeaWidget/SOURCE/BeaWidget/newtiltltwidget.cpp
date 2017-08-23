#include "newtiltltwidget.h"
#include "ui_newtiltltwidget.h"
#include "logindialog.h"
#include <QDate>
#include <QTime>
#include <QList>
#include <QDebug>

newTiltltWidget::newTiltltWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTiltltWidget)
{
    ui->setupUi(this);
    this->setFixedSize(parent->width(),parent->height());   //Shang
    closeBtnTimer = 0;
    selfCheck = NULL;
    curTimeShowTimer = NULL;
    startDateTime = QDateTime::currentDateTime();
    if(!selfCheck)
    {
        selfCheck=new SelfCheckThread();
    }
    ui->localState->setText("本地自检");
    ui->stateLight->setFixedSize(15,15);

    //“退出”按钮延时响应 yangmeng 161021
    if(!closeBtnTimer)
    {
        closeBtnTimer = new QTimer();
    }

    button_list = this->findChildren<QToolButton *>();
    for(int i=0;i<button_list.count();i++)
    {
        if(i == 5)
        {
            connect(button_list.at(5),SIGNAL(pressed()),this,SLOT(closeBtn_timestart()));
            connect(button_list.at(5),SIGNAL(released()),this,SLOT(closeBtn_timestop()));
            connect(closeBtnTimer,SIGNAL(timeout()),this,SLOT(closeBtn_count()));
        }
        else
        {
            connect(button_list.at(i),SIGNAL(clicked()),this,SLOT(turnpage()));
        }
    }
    if(userLevel == 0)
    {
        button_list.at(4)->show();
    }
    else
    {
        button_list.at(4)->hide();
    }

    connect(selfCheck,SIGNAL(sig_selfCheck(int)),this,SLOT(selfCheckState(int)));
    ui->time_bar->setFixedWidth(280);
    this->translatelanguage();
//    this->initShow();

    if(!curTimeShowTimer)
    {
       curTimeShowTimer = new QTimer(this);
    }
    connect(curTimeShowTimer,SIGNAL(timeout()),this,SLOT(showCurTime()));
    curTimeShowTimer->start(1000);
    showColon = true;
    selfCheck->start();//设备自检开始
    ui->stateLight->hide();
    ui->localState->hide();

    //Shang
    slot_checkIcon("facilityManageButton");

    //时间戳安装时间过滤器
    ui->lbl_startTime->installEventFilter(this);
    ui->lbl_time->installEventFilter(this);
    ifOpen = true;
}

newTiltltWidget::~newTiltltWidget()
{
    if(closeBtnTimer)
    {
        closeBtnTimer = 0;
    }
    if(selfCheck)
    {
        selfCheck = NULL;
    }
    if(curTimeShowTimer)
    {
        curTimeShowTimer = NULL;
    }
    delete ui;
}

void newTiltltWidget::translatelanguage()
{
        button_list.at(0)->setText("");
        button_list.at(1)->setText("");
        button_list.at(2)->setText("");
        button_list.at(3)->setText("");
        button_list.at(4)->setText("");
        button_list.at(5)->setText("");
}

void newTiltltWidget::initShow()
{

}

void newTiltltWidget::turnFirstPage(int index)
{
    if(index==0)
    {
//        button_list.at(0)->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0,"
//                                         "stop:0 rgba(200,200,200,0),"
//                                         "stop:0.5 rgba(230,230, 230, 50),"
//                                         "stop:1 rgba(240, 240, 240, 130));"
//                                         "font: 75;"
//                                         "color: rgb(255, 255, 255);"
//                                         "border-radius:3px;"
//                                         "border:0px;");
    }
}

void newTiltltWidget::turnpage()
{
    int current_index;
    QString buttonName = QObject::sender()->objectName();

    for(int i=0;i<button_list.count();i++)
    {
        if(buttonName == button_list.at(i)->objectName())
        {
            current_index = i;
            slot_checkIcon(buttonName);
            break;
        }

    }
    if(current_index<button_list.count()-1)
    {
        emit turnpage(current_index);
    }
    else
    {
        emit closeMainWindow();
    }

}

//“退出”按钮延时响应 yangmeng 161021 start
void newTiltltWidget::closeBtn_timestart()
{
    closeBtnTimer->start(300);
}

void newTiltltWidget::closeBtn_count()
{
    closeBtn_time++;
    if(closeBtn_time>2)
    {
        emit closeMainWindow();
        closeBtnTimer->stop();
        closeBtn_time = 0;
    }
}

void newTiltltWidget::showCurTime()
{
    QString curDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString curTime = QTime::currentTime().toString("hh:mm:ss");
    QDateTime endDateTime = QDateTime::currentDateTime();
    int runTime = startDateTime.secsTo(endDateTime);
    QString days = QString::number(runTime/86400);
    ui->lbl_startTime->setText("运行时间：" + days  + "天 " +QDateTime::fromTime_t(runTime).toUTC().toString("hh:mm:ss"));
    ui->lbl_time->setText(curDate+" "+curTime);
}

void newTiltltWidget::closeBtn_timestop()
{
    closeBtnTimer->stop();
    closeBtn_time = 0;
}
//“退出”按钮延时响应 yangmeng 161021 stop

void newTiltltWidget::selfCheckState(int status)//1故障，0正常
{
    if(status)
    {
         QPixmap switch_pix_red(":/img/img/red.png");
         ui->stateLight->setPixmap(switch_pix_red);
    }
    else
        {
        QPixmap switch_pix_green(":/img/img/green.png");
        ui->stateLight->setPixmap(switch_pix_green);
    }
}

//改变用户角色 yangmeng161022
void newTiltltWidget::changeUser()
{
    if(userLevel == 0)  //管理员
    {
        button_list.at(4)->show();
//        button_list.at(4)->setStyleSheet("font:75;"
//                                         "color: rgb(255,255,255);"
//                                         "border-radius:3px;"
//                                         "border-style:flat;");
    }
    else                     //普通用户
    {
        button_list.at(4)->hide();
    }
    emit turnpage(0);
}

//Shang
void newTiltltWidget::slot_checkIcon(QString buttonName)
{
    if(buttonName == "facilityManageButton")
    {
        ui->facilityManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shbgl+.png);");
        ui->realtimeMonitorButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shshjk.png);");
        ui->statiaticalControlButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tjgl.png);");
        ui->offlineQueryButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/lxchx.png);");
        ui->userManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/yhgl.png);");
        ui->exitButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tchxt.png); ");
    }
    else if(buttonName == "realtimeMonitorButton")
    {
        ui->facilityManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shbgl.png);");
        ui->realtimeMonitorButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shshjk+.png);");
        ui->statiaticalControlButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tjgl.png);");
        ui->offlineQueryButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/lxchx.png);");
        ui->userManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/yhgl.png);");
        ui->exitButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tchxt.png); ");
    }
    else if(buttonName == "statiaticalControlButton")
    {
        ui->facilityManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shbgl.png);");
        ui->realtimeMonitorButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shshjk.png);");
        ui->statiaticalControlButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tjgl+.png);");
        ui->offlineQueryButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/lxchx.png);");
        ui->userManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/yhgl.png);");
        ui->exitButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tchxt.png); ");
    }
    else if(buttonName == "offlineQueryButton")
    {
        ui->facilityManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shbgl.png);");
        ui->realtimeMonitorButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shshjk.png);");
        ui->statiaticalControlButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tjgl.png);");
        ui->offlineQueryButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/lxchx+.png);");
        ui->userManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/yhgl.png);");
        ui->exitButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tchxt.png); ");
    }
    else if(buttonName == "userManageButton")
    {
        ui->facilityManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shbgl.png);");
        ui->realtimeMonitorButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/shshjk.png);");
        ui->statiaticalControlButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tjgl.png);");
        ui->offlineQueryButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/lxchx.png);");
        ui->userManageButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/yhgl+.png);");
        ui->exitButton->setStyleSheet("border-image: url(:/buttontitle/Button/title/tchxt.png); ");
    }
    else
    {

    }

}

void newTiltltWidget::initPixMap()
{


}

void newTiltltWidget::initWidgetShow()
{
    //Shang
    slot_checkIcon("facilityManageButton");
}

//LYS-catch timeLabel mousedoubleclick event
bool newTiltltWidget::eventFilter(QObject *obj, QEvent *event)
{
    QString objName = obj->objectName();
    if(objName == ui->lbl_startTime->objectName() || objName == ui->lbl_time->objectName())
    {
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            if(ifOpen)
            {
               ifOpen = false;
               emit ifAlarmChanged(ifOpen);
            }
            else
            {
                ifOpen = true;
                emit ifAlarmChanged(ifOpen);
            }
            return true;
        }
    }
    else
    {
        return QWidget::eventFilter(obj,event);
    }
}
