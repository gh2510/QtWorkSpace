#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H

#include <QDialog>
//#include "capturewidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"commonbutton.h"
#include"capturethread.h"
#include <QSqlQuery>

namespace Ui {
class capturedialog;
}

class capturedialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit capturedialog(QWidget *parent = 0);
    ~capturedialog();

public slots:
    void slot_start();
    void slot_stop();
    void slot_close();

private:
    Ui::capturedialog *ui;
    commonButton *start;
    commonButton *stop;
    commonButton *close;
   // capturewidget  *cap_widget;    //端口镜像
    QHBoxLayout *mainLayout1;
    QHBoxLayout *mainLayout2;
    QVBoxLayout *topLayout;
    CaptureThread *captureThread,*captureThread1; // gaohao Add 捕获多个镜像口数据
};

#endif // CAPTUREDIALOG_H
