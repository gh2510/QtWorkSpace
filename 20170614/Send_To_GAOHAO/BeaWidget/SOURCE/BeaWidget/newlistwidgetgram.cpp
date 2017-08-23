#include "newlistwidgetgram.h"
#include "ui_newlistwidgetgram.h"
#include <QDebug>

NewListWidgetGram::NewListWidgetGram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewListWidgetGram)
{
    ui->setupUi(this);
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<parent->width()<<parent->height()
           <<"\n";
    setFixedSize(parent->width(),parent->height()*9.5/10);
//    button_list = this->findChildren<QToolButton*>();
    button_list.append(ui->thresholdBtn);
    button_list.append(ui->troubleShootGuidBtn);
    button_list.append(ui->realtimeLogBtn);
    button_list.append(ui->logQueryBtn);
    for(int i=0;i<button_list.count();i++)
    {
        connect(button_list.at(i),SIGNAL(clicked()),
                this,SLOT(turnpage()));
        button_list.at(i)->setText(tr(""));
    }
    slot_WidgetShow("thresholdBtn");
}

void NewListWidgetGram::translatelanguage()
{
    button_list.at(0)->setText(tr(""));
    button_list.at(1)->setText(tr(""));     //yangmeng 161026 根据要求修改
    button_list.at(2)->setText(tr(""));     //qhy 2016.11.28
    button_list.at(3)->setText(tr(""));     //qhy 2016.11.28
}

void NewListWidgetGram::turnToFirstPage()
{
    //默认切换到第一页
//    slot_WidgetShow("thresholdBtn");
}

void NewListWidgetGram::turnpage()
{
    QString btnName = QObject::sender()->objectName();
    int current_index;
    for(int i=0;i<button_list.count();i++)
    {
        if(btnName == button_list.at(i)->objectName())
        {
            current_index = i;
            slot_WidgetShow(btnName);
            break;
        }
    }

    emit turnpage(current_index);

}

//Shang
void NewListWidgetGram::slot_WidgetShow(QString buttonname)
{
    if(buttonname == "thresholdBtn")
    {
        ui->thresholdBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/yzhshzh+.png);");
        ui->troubleShootGuidBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/pgzhn.png);");
        ui->realtimeLogBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/shshrzh.png);");
        ui->logQueryBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/rzhchx.png);");
    }
    else if(buttonname == "troubleShootGuidBtn")
    {
        ui->thresholdBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/yzhshzh.png);");
        ui->troubleShootGuidBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/pgzhn+.png);");
        ui->realtimeLogBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/shshrzh.png);");
        ui->logQueryBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/rzhchx.png);");
    }
    else if(buttonname == "realtimeLogBtn")
    {
        ui->thresholdBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/yzhshzh.png);");
        ui->troubleShootGuidBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/pgzhn.png);");
        ui->realtimeLogBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/shshrzh+.png);");
        ui->logQueryBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/rzhchx.png);");
    }
    else if(buttonname == "logQueryBtn")
    {
        ui->thresholdBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/yzhshzh.png);");
        ui->troubleShootGuidBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/pgzhn.png);");
        ui->realtimeLogBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/shshrzh.png);");
        ui->logQueryBtn->setStyleSheet("border-image: url(:/buttonlist/Button/list/rzhchx+.png);");
    }
    else
    {

    }
}

NewListWidgetGram::~NewListWidgetGram()
{
    delete ui;
}
