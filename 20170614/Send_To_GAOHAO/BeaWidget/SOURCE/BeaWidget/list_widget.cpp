#include"logindialog.h"
#include "list_widget.h"
#include "ListButton.h"
#include "mainwindow.h"

/*
ListWidget::ListWidget(QWidget *parent):QWidget(parent)
{
    QStringList str_list;
    if(userLevel==0)
    str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
            <<":/toolWidget/toolWidget/jiaSu";
    else
        str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
                ;
    button_layout=new QVBoxLayout();
    button_layout->addStretch();
    signal_mapper=new QSignalMapper(this);
     setFixedWidth(parent->width()/6);
    for(int i=0;i<str_list.size();i++)
    {
        ListButton * tool_button=new ListButton(str_list.at(i));

        tool_button->setFixedWidth(this->width()-20);
        button_list.append(tool_button);
        connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(tool_button,QString::number(i,10));
        button_layout->addWidget(tool_button,0,Qt::AlignHCenter);
        button_layout->addStretch();
    }

    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(turnpage(QString)));


    this->translatelanguage();

    setLayout(button_layout);   
    is_move=false;

}*/

//yangmeng  161022 开机默认创建所有按键，但界面只显示默认进入的普通用户权限内容
ListWidget::ListWidget(QWidget *parent):QWidget(parent)
{

    //    if(userLevel==0)
//    str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
//            <<":/toolWidget/toolWidget/jiaSu";
//    else
//        str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
//                ;
    str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"<<":/toolWidget/toolWidget/portMon"
              <<":/toolWidget/toolWidget/jiaSu"  ;

    button_layout=new QVBoxLayout();
    button_layout->addStretch();
    signal_mapper=new QSignalMapper(this);
//     setFixedWidth(parent->width()/6);
    for(int i=0;i<str_list.size();i++)
    {
        ListButton * tool_button=new ListButton(str_list.at(i));

        tool_button->setFixedWidth(this->width()-20);
        qDebug()<<__FILE__<<__LINE__<<"\n"
               <<"tool_button:"<<tool_button->width()<<tool_button->height()
               <<"\n";
        button_list.append(tool_button);
        connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(tool_button,QString::number(i,10));

        if((userLevel==0)||(str_list.at(i) != ":/toolWidget/toolWidget/jiaSu"))
        {
            button_layout->addWidget(tool_button,0,Qt::AlignHCenter);
            button_layout->addStretch();
        }
        //button_layout->addWidget(tool_button,0,Qt::AlignHCenter);
    }

    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(turnpage(QString)));


    this->translatelanguage();

    setLayout(button_layout);
    is_move=false;

}

ListWidget::~ListWidget()
{
    if(button_layout)delete button_layout;
}

void ListWidget::paintEvent(QPaintEvent * e)
{
     QPainter * painter=new QPainter(this);
    QPen pen(Qt::NoBrush,1);
    painter->setPen(pen);
    QLinearGradient linear(rect().topLeft(),rect().topRight());
    linear.setColorAt(0,QColor(26,28,26));
    linear.setColorAt(0.5,QColor(20,70,70));
    linear.setColorAt(1,QColor(26,28,26));
    painter->setBrush(linear);
    painter->drawRect(rect());
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(3,3,this->width()-6,this->height()-6);
    painter->setRenderHint(QPainter::Antialiasing,true);

    QColor color(137,137,130,178);

    for(int i=0;i<3;i++)
    {
        QPainterPath patht;
        patht.setFillRule(Qt::WindingFill);
        path.addRect(3-i,3-i,this->width()-(3-i)*2,this->height()-(3-i)*2);
        color.setAlpha((200-qSqrt(i)*50));
        painter->setPen(color);
        painter->drawPath(path);
    }
   delete painter;
}
void ListWidget::translatelanguage()
{
    ///这里有越界风险
    button_list.at(0)->setText(tr("拓扑视图"));
    button_list.at(1)->setText(tr("告警查询"));
    button_list.at(2)->setText(tr("交换机管理"));
    button_list.at(3)->setText(tr("端口镜像"));
    if(userLevel==0)
        button_list.at(4)->setText(tr("配置管理"));
}

void ListWidget::turnpage(QString current_page)
{
    bool ok;
    int current_index=current_page.toInt(&ok,10);
    for(int i=0;i<button_list.count();i++)
    {
        ListButton *tool_buttom=button_list.at(i);
        if(current_index==3)break;
        if(current_index==i)
        {
           tool_buttom->setMousePress(true);
        }
        else
        {
            tool_buttom->setMousePress(false);
        }
    }
    emit turnpage(current_index);
}

//改变用户角色 yangmeng161022
void ListWidget::changeUser()
{
    if(userLevel == 0)  //管理员
    {
        for(int i=0;i<str_list.size();i++)
        {
            if(str_list.at(i) == ":/toolWidget/toolWidget/jiaSu")
            {
                ListButton * list_button=button_list.at(i);
                //button_layout->addWidget(i,list_button,0,Qt::AlignHCenter);
                button_layout->addWidget(list_button,0,Qt::AlignHCenter);
                button_layout->addStretch();
                list_button->show();
                this->translatelanguage();

            }
        }
    }
    else                     //普通用户
    {
        for(int i=0;i<str_list.size();i++)
        {
            if(str_list.at(i) == ":/toolWidget/toolWidget/jiaSu")
            {
                ListButton * tool_button=button_list.at(i);
                button_layout->removeWidget(tool_button);
                button_layout->removeItem(button_layout->itemAt(2*i+1));
                tool_button->hide();
                this->translatelanguage();

            }
        }
    }
}

