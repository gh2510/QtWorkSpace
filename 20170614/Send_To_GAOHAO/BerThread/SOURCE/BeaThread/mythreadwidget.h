#ifndef MYTHREADWIDGET_H
#define MYTHREADWIDGET_H

#include <QWidget>
#include "myudprecv.h"
#include"capturethread.h"
#include <QSqlQuery>

namespace Ui {
class MyThreadWidget;
}

class MyThreadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyThreadWidget(QWidget *parent = 0);
    ~MyThreadWidget();

private slots:
    void dealUDP(int udptype);
    void slot_start();
    void slot_stop();

private:
    Ui::MyThreadWidget *ui;
    MyUdpRecv *myudp;

    CaptureThread *captureThread,*captureThread1; // gaohao Add 捕获多个镜像口数据


};

#endif // MYTHREADWIDGET_H
