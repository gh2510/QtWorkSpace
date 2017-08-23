#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include<captureimage.h>
class CaptureThread : public QThread
{
    Q_OBJECT
public:
    explicit CaptureThread(QObject *parent = 0);
    ~ CaptureThread();
    void setFile(char portName[],double num,double size, QString path); // gaohao Add 增加传递端口参数
    void run();
    void stop();

    void setAdapterID(int id);      //yangmeng 161030 设置当前是网卡1还是网卡2
signals:
    
public slots:

private:
    CaptureImage *captureImage;
    
};

#endif // CAPTURETHREAD_H
