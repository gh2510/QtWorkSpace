#ifndef TOOLBUTTON_DIY_H
#define TOOLBUTTON_DIY_H
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>
class ToolButtonDiy : public QToolButton
{
public:
    explicit ToolButtonDiy(QString pic_name,QWidget *parent=0);
    ~ToolButtonDiy();
    void setMousePress(bool mouse_press);

private:
    void enterEvent(QEvent * e);
    void leaveEvent(QEvent * e);
//    void mousePressEvent(QMouseEvent * e);        //yangmeng 161022 取消自定义按钮按下响应
    void paintEvent(QPaintEvent * e);
    void painterinfo(int top_color,int middle_color,int bottom_color);

public:
    bool mouse_over;
    bool mouse_press;
};

#endif // TOOLBUTTON_DIY_H
