#include "mainframe.h"

MainFrame::MainFrame(QWidget *parent) :QDialog(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    mouse_press=false;

}

MainFrame::~MainFrame()
{

}

void MainFrame::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,this->width()-20,this->height()-20);


    QColor color(26,28,26,50);
   // QColor color(47,71,127,50);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(color);
    painter.fillPath(path,QBrush(QColor(26,28,26)));

    QPen pen(color,2);

    int p_num=10;
    for(int i=p_num-1;i>=0;i--)    {


          int arcR = p_num;    //弧度

        //   QPainterPath path;
           //逆时针

           path.setFillRule(Qt::WindingFill);
           path.moveTo(arcR,i);
           path.arcTo(i, i, arcR * 2, arcR * 2, 90.0f, 90.0f);

           path.lineTo(i,this->height()-arcR-i);
           path.arcTo(i,this->height()-i-arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
           path.lineTo(this->width()-i-arcR, this->height()-i);
           path.arcTo(this->width()-i-arcR * 2, this->height()-i-arcR * 2, arcR * 2, arcR * 2, 270.0f, 90.0f);
           path.lineTo(this->width()-i,i+arcR);
           path.arcTo( this->width()-i-arcR * 2,i, arcR * 2, arcR * 2, 0.0f, 90.0f);
           path.lineTo(arcR,i);
           color.setAlpha((150-qSqrt(i)*50));
           pen.setColor(color);
           painter.setPen(pen);
           painter.drawPath(path);
    }
}

void MainFrame::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mouse_press=true;
        mouse_point=event->pos();

    }
}

void MainFrame::mouseMoveEvent(QMouseEvent *event)
{
  if(mouse_press)
  {
       QPoint move_pos=event->globalPos();
       this->move(move_pos-mouse_point);
  }

}
void MainFrame::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press=false;
}
