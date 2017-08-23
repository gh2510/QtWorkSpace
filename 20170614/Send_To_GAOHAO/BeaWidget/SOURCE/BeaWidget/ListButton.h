#ifndef LISTBUTTON_H
#define LISTBUTTON_H
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class ListButton : public QToolButton
{
public:
    explicit ListButton(QString pic_name,QWidget *parent=0);
    ~ListButton();
    void setMousePress(bool mouse_press);
private:
    void enterEvent(QEvent * e);
    void leaveEvent(QEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void paintEvent(QPaintEvent * e);
    void painterinfo(int top_color,int middle_color,int bottom_color);
public:
    bool mouse_over;
    bool mouse_press;
};


#endif // LISTBUTTON_H
