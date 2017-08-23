#include "switchstateview.h"
#include "ui_switchstateview.h"

#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QApplication>
#include <QDesktopWidget>
SwitchStateView::SwitchStateView(QWidget *parent) :
    QWidget(parent),ui(new Ui::SwitchStateView)
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"hehe SwitchStateView"<<parent->width()<<parent->height()
           <<"\n";
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    v_layout=new QVBoxLayout();

    //正常
    switch_pix_green=new QPixmap(":/images/images/green.png");

    //告警
    switch_pix_red=new QPixmap(":/images/images/red.png");

    //关闭
    switch_pix_gray=new QPixmap(":/images/images/gray.png");

    //测试
    switch_pix_yellow = new QPixmap(":/images/images/yellow.png");

    int i;
    for( i=0;i<SWITCH_NUM;)
    {
        int k=i;
        QHBoxLayout *h_layout=new QHBoxLayout();
        for( ;i<SWITCH_NUM && i<k+LINE_NUM;i++)
        {
            QVBoxLayout *top_text_layout=new QVBoxLayout();
            QLabel * lbltxt=new QLabel();
            QString s = QString::number(i+1, 10);
            lbltxt->setText(s);
            lbltxt->setPalette(pe);
            QFont font  = lbltxt->font();
            font.setPointSize(8);
            lbltxt->setFont(font);
            txt_list.append(lbltxt);

            QLabel * label=new QLabel();
            label->setStyleSheet("border-radius:1px;");
            QSize size_pix(15,15);
            label->setPixmap(switch_pix_gray->scaled(size_pix,Qt::KeepAspectRatioByExpanding));
            label->setFixedSize(15,15);

            //yangmeng 颠倒交换机端口图片和序号的位置 2016.10.13
            top_text_layout->addWidget(label,0,Qt::AlignHCenter);
            top_text_layout->addWidget(lbltxt,0,Qt::AlignHCenter);

            h_layout->addLayout(top_text_layout);
            h_layout->addSpacing(1);
            pix_list.append(label);
        }
        v_layout->addLayout(h_layout);
        v_layout->addSpacing(3);
    }

    lbltitle=new QLabel();
    lbltitle->setText("switchA");
    lbltitle->setStyleSheet("color:rgb(255,255,255);");
    QVBoxLayout *right_v_layout=new QVBoxLayout();
    right_v_layout->addStretch(1);
    right_v_layout->addWidget(lbltitle,0,Qt::AlignHCenter);
    right_v_layout->addStretch(2);
    right_v_layout->addLayout(v_layout);
    right_v_layout->addStretch(1);
    ui->frame->setLayout(right_v_layout);
}

void SwitchStateView:: change_port_state(int port_id,int state)
{
    //  Modify 添加warn状态显示
//    qDebug()<<"state，"<<state<<"____port_id:"<<port_id;
    switch(state)
       {
         case switchUp:     // 正常
            pix_list.at(port_id)->setPixmap(switch_pix_green->scaled(QSize(15,15),Qt::KeepAspectRatioByExpanding));
            break;
         case switchTest:   // 测试
            pix_list.at(port_id)->setPixmap(switch_pix_yellow->scaled(QSize(15,15),Qt::KeepAspectRatioByExpanding));
            break;
         case switchDown:   // 关闭
            pix_list.at(port_id)->setPixmap(switch_pix_gray->scaled(QSize(15,15),Qt::KeepAspectRatioByExpanding));
            break;
        case switchWarn:    // 告警
            pix_list.at(port_id)->setPixmap(switch_pix_red->scaled(QSize(15,15),Qt::KeepAspectRatioByExpanding));
            break;
         default:
            pix_list.at(port_id)->setPixmap(switch_pix_green->scaled(QSize(15,15),Qt::KeepAspectRatioByExpanding));
     }
}

void SwitchStateView::setSwitchType( int  type)
{
    switch(type)
    {
        case TTM:  for(int i=0;i<60;i++) {txt_list.at(i)->setVisible(true);pix_list.at(i)->setVisible(true);}
            break;
        case FETM:  for(int i=0;i<52;i++) {txt_list.at(i)->setVisible(true);pix_list.at(i)->setVisible(true);}
                          for(int i=52;i<60;i++) {txt_list.at(i)->setVisible(false);pix_list.at(i)->setVisible(false);}
            break;
        case TFTM:  for(int i=0;i<28;i++) {txt_list.at(i)->setVisible(true);pix_list.at(i)->setVisible(true);}
                          for(int i=28;i<60;i++) {txt_list.at(i)->setVisible(false);pix_list.at(i)->setVisible(false);}
            break;
    }
}

void SwitchStateView::setTitle(QString title)
{
    this->lbltitle->setText(title);
}

SwitchStateView::~SwitchStateView()
{
    delete switch_pix_gray;
    delete switch_pix_red;
    delete switch_pix_green;
    delete switch_pix_yellow;
    for(int i=0;i<pix_list.size();i++)
        delete pix_list.at(i);
    for(int i=0;i<txt_list.size();i++)
        delete txt_list.at(i);

    delete lbltitle;
    delete v_layout;

}

void SwitchStateView::paintEvent(QPaintEvent * event)
{
//    QPainter * painter=new QPainter(this);
//    QPen pen(Qt::NoBrush,1);
//    painter->setPen(pen);
//    QLinearGradient linear(rect().topLeft(),rect().topLeft());
//    linear.setColorAt(0,QColor(114,111,128));
//    linear.setColorAt(0.5,QColor(20,70,70));
//    linear.setColorAt(1,QColor(114,111,128));
//    painter->setBrush(linear);
//    painter->drawRect(rect());
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(3,3,this->width()-6,this->height()-6);
//    painter->setRenderHint(QPainter::Antialiasing,true);
//    QColor color(131,175,155,178);
//    for(int i=0;i<3;i++)
//    {
//        QPainterPath patht;
//        patht.setFillRule(Qt::WindingFill);
//        path.addRect(3-i,3-i,this->width()-(3-i)*2,this->height()-(3-i)*2);
//        color.setAlpha((200-qSqrt(i)*50));
//        painter->setPen(color);
//        painter->drawPath(path);
//    }
//    delete painter;
}
