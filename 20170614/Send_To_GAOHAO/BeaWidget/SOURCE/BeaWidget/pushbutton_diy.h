#ifndef PUSHBUTTON_DIY_H
#define PUSHBUTTON_DIY_H
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class PushButtonDIY : public QPushButton
{
  Q_OBJECT
 public:
   explicit PushButtonDIY(QWidget *parent=0);
     ~PushButtonDIY();
    void setPicName(QString picName);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
 signals:
    void buttonclicked();
 private:
    enum ButtonStatus{NORMAL,ENTER,PRESS,NOSTATUS};
    ButtonStatus status;
    QString pic_name;
    
    int b_width;   //width of the button
    int b_height;  //height of the button
    bool mouse_press;//whether mousedown
};

#endif // PUSHBUTTON_DIY_H
