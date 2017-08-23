#include "title_widget.h"
#include "toolbutton_diy.h"
#include "mainwindow.h"
#include"logindialog.h"

TitleWidget::TitleWidget(QWidget *parent):QWidget(parent)
{

    QPixmap switch_pix_green(":/img/img/green.png");
    selfCheck=new SelfCheckThread();

    localState=new QLabel();
    stateLight=new QLabel();
    localState->setText("本地自检");
    stateLight->setPixmap(switch_pix_green);
    stateLight->setFixedSize(15,15);
    QPalette   pal;
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    localState->setPalette(pal);
    QFont font3;
    font3.setFamily(QString::fromUtf8("Tahoma"));
    font3.setPointSize(8);
    font3.setBold(true);
    font3.setWeight(75);
    localState->setFont(font3);

    //“退出”按钮延时响应 yangmeng 161021
    closeBtn_time = 0;
    closeBtnTimer = new QTimer();
    painter = NULL;


/*      //帮助页面去掉<<":/toolWidget/toolWidget/help"
    if(userLevel==0)//管理员
        str_list<<":/toolWidget/toolWidget/switch"<<":/toolWidget/toolWidget/watch"<<":/toolWidget/toolWidget/tongji"<<":/toolWidget/toolWidget/shebei"
               <<":/toolWidget/toolWidget/shezhi"<<":/toolWidget/toolWidget/user"<<":/toolWidget/toolWidget/exit";
    else
    str_list<<":/toolWidget/toolWidget/switch"<<":/toolWidget/toolWidget/watch"<<":/toolWidget/toolWidget/tongji"<<":/toolWidget/toolWidget/shebei"
           <<":/toolWidget/toolWidget/shezhi"<<":/toolWidget/toolWidget/exit";

    button_layout=new QHBoxLayout();
    signal_mapper=new QSignalMapper(this);
    for(int i=0;i<str_list.size();i++)
    {
        ToolButtonDiy * tool_button=new ToolButtonDiy(str_list.at(i));
        QPalette t_palette=tool_button->palette();
        t_palette.setColor(QPalette::ButtonText,Qt::white);
        tool_button->setPalette(t_palette);
        button_list.append(tool_button);
        connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(tool_button,QString::number(i,10));
        button_layout->addWidget(tool_button,0,Qt::AlignBottom);
    }*/

    //yangmeng 161022 初始化时创建所有按钮，以便用户切换
    //<<":/toolWidget/toolWidget/shebei" 端口镜像，取消
    str_list<<":/toolWidget/toolWidget/switch"<<":/toolWidget/toolWidget/watch"<<":/toolWidget/toolWidget/tongji"
           <<":/toolWidget/toolWidget/shezhi"<<":/toolWidget/toolWidget/user"<<":/toolWidget/toolWidget/exit";

    button_layout=new QHBoxLayout();
    signal_mapper=new QSignalMapper(this);
    for(int i=0;i<str_list.size();i++)    //退出按钮延时响应 yangmeng161021
    {
        ToolButtonDiy * tool_button=new ToolButtonDiy(str_list.at(i));
        QPalette t_palette=tool_button->palette();
        t_palette.setColor(QPalette::ButtonText,Qt::white);
        tool_button->setPalette(t_palette);
        button_list.append(tool_button);

        //yangmeng161021 特殊按钮处理
        if(str_list.at(i) == ":/toolWidget/toolWidget/exit")
        {
            connect(tool_button,SIGNAL(pressed()),this,SLOT(closeBtn_timestart()));
            connect(tool_button,SIGNAL(released()),this,SLOT(closeBtn_timestop()));
            connect(closeBtnTimer,SIGNAL(timeout()),this,SLOT(closeBtn_count()));
        }
        else
        {
            connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
            signal_mapper->setMapping(tool_button,QString::number(i,10));
        }
        if((userLevel==0)||(str_list.at(i) != ":/toolWidget/toolWidget/user"))
        {
            button_layout->addWidget(tool_button,0,Qt::AlignBottom);
        }

    }

    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(turnpage(QString)));
    connect(selfCheck,SIGNAL(sig_selfCheck(int)),this,SLOT(selfCheckState(int)));
    time_bar=new StateBar();
    time_bar->setFixedWidth(280);
    button_layout->addStretch();

   // button_layout->addWidget(localState);
    //button_layout->addWidget(stateLight);//设备自检灯暂时隐藏

    button_layout->addWidget(time_bar);//本地时间
    button_layout->setSpacing(8);
    button_layout->setContentsMargins(15,0,15,0);
    main_layout=new QVBoxLayout();
    main_layout->addLayout(button_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);

    this->translatelanguage();
    setLayout(main_layout);   
    is_move=false;
    selfCheck->start();//设备自检开始
}

TitleWidget::~TitleWidget()
{
    if(painter)delete painter;
    if(time_bar)delete time_bar;
    for(int i=0;i<button_list.size();i++)
         delete button_list.at(i);
    if(signal_mapper)delete signal_mapper;
    if(button_layout) delete button_layout;
    if(main_layout)delete  main_layout;
    if(selfCheck)delete selfCheck;

}

void TitleWidget::translatelanguage()
{


    if(userLevel==0)//管理员
    {
        button_list.at(0)->setText(tr("设备管理"));
        button_list.at(1)->setText(tr("实时监控"));
        button_list.at(2)->setText(tr("统计管理"));
       // button_list.at(3)->setText(tr("端口镜像"));
        button_list.at(3)->setText(tr("离线查询"));
        button_list.at(4)->setText(tr("用户管理"));
       // button_list.at(6)->setText(tr("帮助"));
        button_list.at(5)->setText(tr("退出"));

    }
    else//普通用户
    {
        button_list.at(0)->setText(tr("设备管理"));
        button_list.at(1)->setText(tr("实时监控"));
        button_list.at(2)->setText(tr("统计管理"));
       // button_list.at(3)->setText(tr("端口镜像"));
        button_list.at(3)->setText(tr("离线查询"));

      // button_list.at(5)->setText(tr("帮助"));
        button_list.at(5)->setText(tr("退出"));  //“退出”按钮延时响应 yangmeng 161021
    }


}

void TitleWidget::paintEvent(QPaintEvent * e)
{
    painter=new QPainter(this);
    QPen pen(Qt::NoBrush,1);
    painter->setPen(pen);
    QLinearGradient linear(rect().topLeft(),rect().bottomLeft());
    linear.setColorAt(0,QColor(15,15,15));
    linear.setColorAt(0.5,QColor(13,96,108));
    linear.setColorAt(1,QColor(15,15,15));
    painter->setBrush(linear);
    painter->drawRect(rect());

    painter->setRenderHint(QPainter::Antialiasing,true);
    delete painter;
    painter = NULL; //yangmeng 161021  防止析构出错
}
void TitleWidget::turnpage(QString current_page)
{
    bool ok;
    int current_index=current_page.toInt(&ok,10);
    for(int i=0;i<button_list.count();i++)
    {
        ToolButtonDiy *tool_buttom=button_list.at(i);
        if(current_index==i)
        {
           tool_buttom->setMousePress(true);
        }
        else
        {
            tool_buttom->setMousePress(false);
        }
    }
    if(current_index<str_list.size()-1)
    {
      emit turnpage(current_index);
    }
    else
    {
        emit closeMainWindow();
    }

}

void TitleWidget::selfCheckState(int status)//1故障，0正常
{
    if(status)
    {
         QPixmap switch_pix_red(":/img/img/red.png");
         stateLight->setPixmap(switch_pix_red);
    }
    else
        {
        QPixmap switch_pix_green(":/img/img/green.png");
        stateLight->setPixmap(switch_pix_green);
    }
}

//改变用户角色 yangmeng161022
void TitleWidget::changeUser()
{
    if(userLevel == 0)  //管理员
    {
        for(int i=0;i<str_list.size();i++)
        {
            if(str_list.at(i) == ":/toolWidget/toolWidget/user")
            {
                ToolButtonDiy * tool_button=button_list.at(i);
                button_layout->insertWidget(i,tool_button,0,Qt::AlignBottom);
                tool_button->show();
                this->translatelanguage();
            }
        }
    }
    else                     //普通用户
    {
        for(int i=0;i<str_list.size();i++)
        {
            if(str_list.at(i) == ":/toolWidget/toolWidget/user")
            {
                ToolButtonDiy * tool_button=button_list.at(i);
                button_layout->removeWidget(tool_button);
                tool_button->hide();
                this->translatelanguage();
            }
        }
    }
}

//“退出”按钮延时响应 yangmeng 161021 start
void TitleWidget::closeBtn_timestart()
{
    closeBtnTimer->start(300);
}

void TitleWidget::closeBtn_count()
{
    closeBtn_time++;
    if(closeBtn_time>2)
    {
        emit closeMainWindow();
        closeBtnTimer->stop();
        closeBtn_time = 0;
    }
}

void TitleWidget::closeBtn_timestop()
{
    closeBtnTimer->stop();
    closeBtn_time = 0;
}
//“退出”按钮延时响应 yangmeng 161021 stop

