#include "capturethread.h"
#include<QDebug>
CaptureThread::CaptureThread(QObject *parent) :
    QThread(parent)
{
    captureImage=new CaptureImage();
}

CaptureThread::~CaptureThread()
{
    if(captureImage) delete captureImage;
}

// gaohao Modify char portName[100] 将镜像口名称作为参数
void CaptureThread::setFile(char portName[100],double num, double size, QString path)
{
    qDebug()<<"port:"<<portName << "   path:"<<path <<endl;
    captureImage->setFile(portName,num,size,path);
}

void CaptureThread::run()
{

    qDebug()<<"线程开始运行0101";

    captureImage->run();

    qDebug()<<"线程运行once";

}

void CaptureThread::stop()
{
    captureImage->setFlag(false);
}

//yangmeng 161030 设置当前是网卡1还是网卡2
void CaptureThread::setAdapterID(int id)
{
    captureImage->setAdapteraID(id);
}
