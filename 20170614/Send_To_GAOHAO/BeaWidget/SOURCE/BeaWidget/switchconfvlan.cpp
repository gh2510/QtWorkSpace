#include "switchconfvlan.h"
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "commonbutton.h"
#include <QPalette>
#include <QLabel>
#include <QSignalMapper>
#include <QPainter>
#include <QPen>
#include <QSqlQuery>

switchConfVlan::switchConfVlan(telnetManager *telm,QWidget *parent) :
    QWidget(parent)
{
    this->telm=telm;
    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *vlanConfLayout1 = new QHBoxLayout();
    QHBoxLayout *vlanConfLayout2 = new QHBoxLayout();
    QHBoxLayout *vlanConfLayout3 = new QHBoxLayout();
    QHBoxLayout *vlanConfLayout4 = new QHBoxLayout();
    QHBoxLayout *vlanConfLayout5 = new QHBoxLayout();
    QHBoxLayout *vlanConfLayout6 = new QHBoxLayout();

    main_layout->addStretch(1);
    main_layout->addLayout(vlanConfLayout1,0);
    main_layout->addStretch(1);
    main_layout->addLayout(vlanConfLayout2,0);
    main_layout->addStretch(5);

    QHBoxLayout *vlan1ConfLayout = new QHBoxLayout();
    QVBoxLayout *vlan1ConfPara = new QVBoxLayout();
    QVBoxLayout *vlan1ConfSubBtn = new QVBoxLayout();
    QHBoxLayout *vlan1ConfLayout2 = new QHBoxLayout();
    QHBoxLayout *vlan1ConfLayout3 = new QHBoxLayout();
    QHBoxLayout *vlan1ConfLayout4 = new QHBoxLayout();
    vlan1ConfPara->addLayout(vlan1ConfLayout2);
    vlan1ConfPara->addLayout(vlan1ConfLayout3);
    vlan1ConfPara->addLayout(vlan1ConfLayout4);
    vlan1ConfLayout->addLayout(vlan1ConfPara);
    vlan1ConfLayout->addSpacing(40);
    vlan1ConfLayout->addLayout(vlan1ConfSubBtn);
    vlan1ConfLayout->addStretch(0);

    vlanConfLayout2->addLayout(vlan1ConfLayout);
    main_layout->addLayout(vlanConfLayout3,0);
    main_layout->addLayout(vlanConfLayout4,0);
    main_layout->addLayout(vlanConfLayout5,0);
    main_layout->addLayout(vlanConfLayout6,0);
    main_layout->addStretch(5);


    QLabel *vlanConf = new QLabel(tr("vlan配置"));
    vlanConfLayout1->addWidget(vlanConf,0,Qt::AlignHCenter);

//    switchSel = new LabelComBox();
//    switchSel->setLabel(tr("选择交换机:"));
//    //switchSel->setMaxVisibleItems(5);


//    QSqlQuery query("",DBConnection::db);;
//    query.exec(QString("select c.name from switch c;"));
//    while(query.next()){
//        switchSel->addItem(query.value(0).toString());
//    }
//    vlan1ConfLayout2->addWidget(switchSel,0,Qt::AlignLeft);

    vlanName = new LabelEdit();
    vlanName->setLabel(tr("vlan名称:"));
    vlanName->setEditReadOnly(false);
    vlan1ConfLayout3->addWidget(vlanName,0,Qt::AlignLeft);

    vlanIP = new LabelEdit();
    vlanIP->setLabel(tr("vlanIP:"));
    vlanIP->setEditReadOnly(false);
    vlan1ConfLayout4->addWidget(vlanIP,0,Qt::AlignLeft);

    commonButton *vlanConfPushBtn = new commonButton();
    vlanConfPushBtn->setText(tr("保存"));
    vlanConfPushBtn->setWidth(100);
    vlan1ConfSubBtn->addWidget(vlanConfPushBtn);


    QSignalMapper * signal_mapper=new QSignalMapper(this);
    QPalette palette;
    palette.setColor(QPalette::ButtonText,QColor("white"));
    for(int i=1;i<=24;i++){
        QCheckBox *port = new QCheckBox("port"+QString::number(i));
        port->setPalette(palette);
        port->setFocusPolicy(Qt::NoFocus);
        list_btn_port.append(port);
        connect(port,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(port,QString::number(i,10));
        if(i<=6){
            vlanConfLayout3->addWidget(port,0,Qt::AlignLeft);

        }
        else if(i<=12){
            vlanConfLayout4->addWidget(port,0,Qt::AlignLeft);
            vlanConfLayout4->addSpacing(4);
        }
        else if(i<=18){
            vlanConfLayout5->addWidget(port,0,Qt::AlignLeft);

        }
        else{
            vlanConfLayout6->addWidget(port,0,Qt::AlignLeft);

        }
    }
    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(checkbox_click(QString)));
    connect(vlanConfPushBtn,SIGNAL(click()),this,SLOT(save_check()));
    this->setLayout(main_layout);

}

void switchConfVlan::save_check( )
{
    if(telm)
    {

    QString IP=vlanIP->text();
    QString vlan_name=vlanName->text();
    telm->confVlan(vlan_name,IP,list_select_port);
    list_select_port.clear();
    }
}

 void switchConfVlan::checkbox_click(QString current_num )
 {
     bool ok;
     int current_index=current_num.toInt(&ok,10);
     if(list_btn_port.at(current_index)->isChecked())
     {
         list_select_port<<current_index;
     }
 }

void switchConfVlan::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawLine(rect().topLeft(),rect().topRight());

}

switchConfVlan::~switchConfVlan()
{

}
