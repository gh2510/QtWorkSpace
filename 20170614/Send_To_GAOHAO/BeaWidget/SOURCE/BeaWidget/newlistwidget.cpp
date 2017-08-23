#include "newlistwidget.h"
#include "ui_newlistwidget.h"
#include"logindialog.h"
#include "mainwindow.h"
#include <QWidget>
#include <QToolButton>

NewListwidget::NewListwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewListwidget)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height()*9.5/10);
    button_list = this->findChildren<QToolButton*>();
    for(int i=0;i<button_list.count();i++)
    {
//        button_list.at(i)->setFixedSize(this->width()-20,55);
        connect(button_list.at(i),SIGNAL(clicked()),this,SLOT(turnpage()));
    }
    if(userLevel == 0)
    {
        button_list.at(4)->show();
    }
    else
    {
        button_list.at(4)->hide();      //hide configManage Button
    }

    translatelanguage();
    slot_WidgetShow("topoViewButton");
}

void NewListwidget::translatelanguage()
{
    button_list.at(0)->setText(tr(""));
    button_list.at(1)->setText(tr(""));
    button_list.at(2)->setText(tr(""));
    button_list.at(3)->setText(tr(""));
    button_list.at(4)->setText(tr(""));
}

void NewListwidget::turnpage()
{
    QString buttonName = QObject::sender()->objectName();
    int curr_index;
    for(int i=0;i<button_list.count();i++)
    {
        if(button_list.at(i)->objectName() == buttonName)
        {
            if(i!=3)
            {
                curr_index = i;
            }
            else
            {
                curr_index = i;
            }
            slot_WidgetShow(buttonName);
            emit turnpage(curr_index);

        }
        else
        {
        }
    }
}

//change user role
void NewListwidget::changeUser()
{
    if(userLevel == 0)  //Administrator
    {
        button_list.at(4)->show();
    }
    else
    {
        button_list.at(4)->hide();  //normal user
    }
}

void NewListwidget::setFirstPressed(int index)
{
    if(index == 0)
    {
        emit turnpage(0);
        slot_WidgetShow("topoViewButton");
    }
}

//Shang
void NewListwidget::slot_WidgetShow(QString buttonName)
{
    if(buttonName == "topoViewButton")
    {
        ui->topoViewButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/tpsht+.png);");
        ui->alarmQueryButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/gjchx.png);");
        ui->switchManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/jhjgl.png);");
        ui->portMirrorButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/dkjx.png);");
        ui->configManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/pzhgl.png);");
    }
    else if(buttonName == "alarmQueryButton")
    {
        ui->topoViewButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/tpsht.png);");
        ui->alarmQueryButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/gjchx+.png);");
        ui->switchManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/jhjgl.png);");
        ui->portMirrorButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/dkjx.png);");
        ui->configManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/pzhgl.png);");
    }
    else if(buttonName == "switchManageButton")
    {
        ui->topoViewButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/tpsht.png);");
        ui->alarmQueryButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/gjchx.png);");
        ui->switchManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/jhjgl+.png);");
        ui->portMirrorButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/dkjx.png);");
        ui->configManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/pzhgl.png);");
    }
//    else if(buttonName == "portMirrorButton")
//    {
//        ui->topoViewButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/拓扑视图.png);");
//        ui->alarmQueryButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/告警查询.png);");
//        ui->switchManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/交换机管理.png);");
//        ui->portMirrorButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/端口镜像+.png);");
//        ui->configManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/配置管理.png);");
//    }
    else if(buttonName == "configManageButton")
    {
        ui->topoViewButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/tpsht.png);");
        ui->alarmQueryButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/gjchx.png);");
        ui->switchManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/jhjgl.png);");
        ui->portMirrorButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/dkjx.png);");
        ui->configManageButton->setStyleSheet("border-image: url(:/buttonlist/Button/list/pzhgl+.png);");
    }
    else
    {

    }
}


NewListwidget::~NewListwidget()
{
    delete ui;
}


