#include "switchconfport.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QSignalMapper>

#include <QPalette>
#include <QPainter>
#include <QPen>
#include <QSqlQuery>
#include "Telnet/telnetmanager.h"

switchConfPort::switchConfPort(telnetManager *telm,QWidget *parent) :
    QWidget(parent)
{
    this->telm=telm;
    main_layout = new QVBoxLayout();
    portConfLayout = new QHBoxLayout();
    portConfPara = new QVBoxLayout();
    portConfSubBtn = new QVBoxLayout();
    portConfLayout1 = new QHBoxLayout();
    portConfLayoutSwitch = new QHBoxLayout();
    portConfLayout2 = new QHBoxLayout();
    portConfLayout3 = new QHBoxLayout();
    portConfLayout4 = new QHBoxLayout();
    portConfLayout5 = new QHBoxLayout();
    portConfPara->addLayout(portConfLayoutSwitch);
    portConfPara->addLayout(portConfLayout2);
    portConfPara->addLayout(portConfLayout3);
    portConfPara->addLayout(portConfLayout4);
    portConfPara->addLayout(portConfLayout5);
    portConfLayout->addLayout(portConfPara);
    portConfLayout->addSpacing(40);
    portConfLayout->addLayout(portConfSubBtn);

    portConfLayout->addStretch(0);
    main_layout->addStretch(1);
    main_layout->addLayout(portConfLayout1);
    main_layout->addStretch(1);
    main_layout->addLayout(portConfLayout);
     main_layout->addStretch(5);
    portConf = new QLabel(tr("端口配置"));\
    portConfLayout1->addWidget(portConf,0,Qt::AlignHCenter);
    portSelect = new LabelComBox();
    portSelect->setLabel(tr("选择端口"));
    for(int i=1;i<=24;i++){
        portSelect->addItem(QString::number(i));
    }
    portConfLayout2->addWidget(portSelect,0,Qt::AlignLeft);

    portStatus = new LabelComBox();
    portStatus->setLabel(tr("端口状态"));
    portStatus->addItem("up");
    portStatus->addItem("down");
    portConfLayout3->addWidget(portStatus,0,Qt::AlignLeft);

    portModel = new LabelComBox();
    portModel->setLabel(tr("端口模式"));
    portModel->addItem("ACCESS");
    portModel->addItem("TRUNK");
    portConfLayout4->addWidget(portModel,0,Qt::AlignLeft);

    portSpeed = new LabelComBox();
    portSpeed->setLabel(tr("端口速率"));
    portSpeed->addItem(tr("10M"));
    portSpeed->addItem(tr("100M"));
    portSpeed->addItem(tr("1000M"));
    portConfLayout5->addWidget(portSpeed,0,Qt::AlignLeft);

    portConfPushBtn = new commonButton();
    portConfPushBtn->setText(tr("保存"));
    portConfPushBtn->setWidth(100);

    portConfSubBtn->addWidget(portConfPushBtn,0,Qt::AlignVCenter);
    connect(portConfPushBtn,SIGNAL(click()),this,SLOT(save_port()));
    this->setLayout(main_layout);
}
void switchConfPort::save_port()
{
    if(telm)
    {
        int port_num=portSelect->text().toInt();
        QString port_sta=portStatus->text();
        QString port_model_t=portModel->text();
        QString port_speed_t=portSpeed->text();
        telm->confPort(port_num,port_sta,port_model_t,port_speed_t);
    }
}

void switchConfPort::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawLine(rect().topLeft(),rect().topRight());

}


switchConfPort::~switchConfPort()
{
    if(portSelect)delete portSelect;
    if(portStatus)delete portStatus;
    if(portModel)delete portModel;
    if(portSpeed)delete portSpeed;
    if(main_layout)delete main_layout;
    if(portConfLayout)delete portConfLayout;
    if(portConfPara)delete portConfPara;
   if(portConfSubBtn)delete portConfSubBtn;
   if(portConfLayout1)delete portConfLayout1;
   if(portConfLayout2)delete portConfLayout2;
   if(portConfLayout3)delete portConfLayout3;
   if(portConfLayout4)delete portConfLayout4;
   if(portConfLayout5)delete portConfLayout5;
   if(portConfLayoutSwitch)delete portConfLayoutSwitch;
    if(portConfPushBtn)delete portConfPushBtn;
    if(portConf)delete portConf;
}
