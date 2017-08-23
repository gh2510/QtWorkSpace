#include "ListButton.h"

ListButton::ListButton(QString pic_name,QWidget *parent):QToolButton(parent)
{
    //set the color of text
    QPalette text_palette=palette();
    text_palette.setColor(QPalette::ButtonText,QColor(230,230,230));
    setPalette(text_palette);

    //set text bold
    QFont &text_font=const_cast<QFont &>(font());
    //text_font.setWeight(QFont::Bold);

    setToolButtonStyle(Qt::ToolButtonTextOnly);

    //set the icon
    QPixmap pixmap(pic_name);
    setIcon(pixmap);
    setIconSize(pixmap.size());

    //set the witdh and height
    setFixedHeight(55);
    setAutoRaise(true);
    setObjectName("transparentToolButton");
    QPalette pl_title;
    pl_title.setColor(QPalette::ButtonText,QColor(255,255,255));
    QToolButton::setPalette(pl_title);
    mouse_over=false;
    mouse_press=false;

}
ListButton::~ListButton()
{

}

void ListButton::enterEvent(QEvent *e)
{
    mouse_over=true;
    QPalette pl_title;
    pl_title.setColor(QPalette::ButtonText,QColor(0,0,0));
    setPalette(pl_title);


    update();
}
void ListButton::leaveEvent(QEvent *e)
{
    mouse_over=false;
    QPalette pl_title;
    pl_title.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pl_title);
    update();
}
void ListButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        emit clicked();
    }
    update();
}
void ListButton::setMousePress(bool mouse_press)
{
    this->mouse_press=mouse_press;
    update();
}
void ListButton::paintEvent(QPaintEvent *e)
{
    if(mouse_over)
    {
        painterinfo(130,50,130);
    }
    else  if(mouse_press)
    {
        painterinfo(130,50,130);
    }

    QToolButton::paintEvent(e);
}

void ListButton::painterinfo(int top_color, int middle_color, int bottom_color)
{
    QPainter painter(this);
    QPen pen(Qt::NoBrush,1);
    painter.setPen(pen);
    QLinearGradient linear(rect().topLeft(),rect().bottomLeft());
    linear.setColorAt(0,QColor(240,240,240,top_color));
    linear.setColorAt(0.5,QColor(230,230,230,middle_color));
    linear.setColorAt(1,QColor(240,240,240,bottom_color));
    painter.setBrush(linear);
    painter.drawRect(rect());
}

