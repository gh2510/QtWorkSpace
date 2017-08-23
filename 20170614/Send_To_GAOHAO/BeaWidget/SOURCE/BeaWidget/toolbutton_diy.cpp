#include "toolbutton_diy.h"

ToolButtonDiy::ToolButtonDiy(QString pic_name,QWidget *parent):QToolButton(parent)
{
    //set the color of text
    QPalette text_palette=palette();
    text_palette.setColor(QPalette::ButtonText,QColor(147,255,255));
    setPalette(text_palette);

    //set text bold
    QFont &text_font=const_cast<QFont &>(font());
    text_font.setWeight(QFont::Bold);
    
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    
    //set the icon
    QPixmap pixmap(pic_name);
    setIcon(pixmap);
    setIconSize(pixmap.size());
    
    //set the witdh and height
    setFixedSize(pixmap.width()+25,pixmap.height()+25);

    setAutoRaise(true);
    setObjectName("transparentToolButton");
    
    mouse_over=false;
    mouse_press=false;
    
}
ToolButtonDiy::~ToolButtonDiy()
{
    
}

void ToolButtonDiy::enterEvent(QEvent *e)
{
    mouse_over=true;
    QPalette pl_title;
     pl_title.setColor(QPalette::ButtonText,QColor(42,92,171));
    setPalette(pl_title);
    update();
}
void ToolButtonDiy::leaveEvent(QEvent *e)
{
    mouse_over=false;
    QPalette pl_title;
    pl_title.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pl_title);
    update();

}
/* yangmeng 161022 取消自定义按钮按下响应
void ToolButtonDiy::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        //emit clicked();
    }
    update();
}*/
void ToolButtonDiy::setMousePress(bool mouse_press)
{
    this->mouse_press=mouse_press;
    update();
}
void ToolButtonDiy::paintEvent(QPaintEvent *e)
{
    if(mouse_over)
    {
        painterinfo(0,50,130);
    }
    else if(mouse_press)
    {
        painterinfo(0,50,130);
    }
    QToolButton::paintEvent(e);
}

void ToolButtonDiy::painterinfo(int top_color, int middle_color, int bottom_color)
{
    QPainter painter(this);
    QPen pen(Qt::NoBrush,1);
    painter.setPen(pen);
    QLinearGradient linear(rect().topLeft(),rect().bottomLeft());
    linear.setColorAt(0,QColor(200,200,200,top_color));
    linear.setColorAt(0.5,QColor(230,230,230,middle_color));
    linear.setColorAt(1,QColor(240,240,240,bottom_color));
    painter.setBrush(linear);
    painter.drawRect(rect());
}
