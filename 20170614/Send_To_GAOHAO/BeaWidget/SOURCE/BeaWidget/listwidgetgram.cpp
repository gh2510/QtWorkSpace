#include "listwidgetgram.h"
#include "ListButton.h"
#include "mainwindow.h"

ListWidgetGram::ListWidgetGram(QWidget *parent):QWidget(parent)
{


    QStringList str_list;
    str_list<<":/toolWidget/toolWidget/muMa"<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
            <<":/toolWidget/toolWidget/jiaSu";

   //  str_list<<":/toolWidget/toolWidget/repair"<<":/toolWidget/toolWidget/qingLi"
     //        <<":/toolWidget/toolWidget/jiaSu";
    button_layout=new QVBoxLayout();
    button_layout->addStretch();
    signal_mapper=new QSignalMapper(this);
    for(int i=0;i<str_list.size();i++)
    {
        ListButton * tool_button=new ListButton(str_list.at(i));

        tool_button->setFixedWidth(80);
        button_list.append(tool_button);
        connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(tool_button,QString::number(i,10));
        button_layout->addWidget(tool_button,0,Qt::AlignHCenter);
        button_layout->addStretch();
    }

    connect(signal_mapper,SIGNAL(mapped(QString)),this,SLOT(turnpage(QString)));


    this->translatelanguage();

    setLayout(button_layout);
    setFixedWidth(100);
    is_move=false;

}

ListWidgetGram::~ListWidgetGram()
{
    if(button_layout)delete button_layout;
}

void ListWidgetGram::paintEvent(QPaintEvent * e)
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
    path.addRect(4,4,this->width()-6,this->height()-6);
    painter->setRenderHint(QPainter::Antialiasing,true);

    QColor color(137,137,130,178);

    for(int i=0;i<button_list.count();i++)
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
void ListWidgetGram::translatelanguage()
{

    button_list.at(0)->setText(tr("阈值设置"));
    //button_list.at(1)->setText(tr("故障信息"));
    button_list.at(1)->setText(tr("排故指南"));     //yangmeng 161026 根据要求修改
    //button_list.at(2)->setText(tr("故障管理"));
    button_list.at(2)->setText(tr("实时日志"));    //qhy 2016.11.28
    button_list.at(3)->setText(tr("日志查询"));    //qhy 2016.11.28
}

void ListWidgetGram::turnpage(QString current_page)
{
    bool ok;
    int current_index=current_page.toInt(&ok,10);
    for(int i=0;i<button_list.count();i++)
    {
        ListButton *tool_buttom=button_list.at(i);
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

