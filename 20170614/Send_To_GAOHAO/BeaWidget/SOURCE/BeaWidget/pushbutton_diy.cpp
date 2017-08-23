#include "pushbutton_diy.h"

PushButtonDIY::PushButtonDIY(QWidget * parent):QPushButton(parent)
{
    status=NOSTATUS;
    mouse_press=false;
}
PushButtonDIY::~PushButtonDIY()
{
    
}

void PushButtonDIY::setPicName(QString picName)
{
    this->pic_name=picName;
    setFixedSize(QPixmap(pic_name).size());
}

void PushButtonDIY::enterEvent(QEvent * event)
{
    status=ENTER;
    update();
}
void PushButtonDIY::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
    {
        mouse_press=true;
        status=PRESS;
        emit buttonclicked();
        update();
    }
}

void PushButtonDIY::mouseReleaseEvent(QMouseEvent * event)
{
    if(mouse_press&&this->rect().contains(event->pos()))
    {
            mouse_press=false;
            status=ENTER;
            update();
    }
}

void PushButtonDIY::leaveEvent(QEvent * event)
{
   status=NORMAL;
   update();
}

void PushButtonDIY::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status)
    {
    case NORMAL: pixmap.load(pic_name);
                  break;
    case ENTER:  pixmap.load(pic_name+QString("_hover"));
                  break;
    case PRESS:  pixmap.load(pic_name+QString("_pressed"));
    case NOSTATUS: pixmap.load((pic_name));
                  break;
    default:    pixmap.load((pic_name));
                  break;
    }
    painter.drawPixmap(this->rect(),pixmap);
}
