#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>

class MainFrame : public QDialog
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget * parent=0);
    ~MainFrame();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);
private:
    QPoint mouse_point;
    bool mouse_press;
};
#endif // MAINFRAME_H
