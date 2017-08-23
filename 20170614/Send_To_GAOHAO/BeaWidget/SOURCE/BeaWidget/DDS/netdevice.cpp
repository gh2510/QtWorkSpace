#include "netdevice.h"
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QDebug>

NetDevice *netDevice = NULL;
NetDevice *NetDevice::getNetDevice(){
    return netDevice;
}

NetDevice::NetDevice(QObject *parent) :
    QObject(parent)
{
    netDevice = this;
    ddsNet = NULL;
    timer = NULL;
}

//初始化设备的网络链接信息
long NetDevice::InitDeviceNet()
{
    long ret = 0;
    if(ddsNet == NULL)
    {
        ddsNet = new DDS_Net();
        ret = ddsNet->InitDDSNet();
    }
    return ret;
}

//释放系统资源
NetDevice::~NetDevice()
{
    if(ddsNet!=NULL)
    {
        delete ddsNet;
        ddsNet = NULL;
    }
    if(timer != NULL)
    {
        delete timer;
        timer = NULL;
    }
    netDevice = NULL;
}

//发送时统信息对外接口
//设置定时发送，timer单位ms，大于0
void NetDevice::SendTimeStateInfo(int time)
{
    if(timer == NULL)
    {
        timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(slot_sendTime()));
    }
    timer->setInterval(time);
    timer->start();
}

//发送时统信息
long NetDevice::slot_sendTime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    TimeStateInfo info;
    memset(&info,0,sizeof(TimeStateInfo));
    info.uchYearHigh = date.year()/100;
    info.uchYearLow = date.year()%100;
    info.uchMonth = date.month();
    info.uchDay = date.daysInMonth();
    info.uchHour = time.hour();
    info.uchMin = time.minute();
    info.uchSec = time.second();
    ddsNet->sendTimeStateInfo(info);
}

//设备接收DDS发送过来的时统信息
void NetDevice::RecvTimeStateInfo(TimeStateInfo info)
{
    QString year = QString("%1%2").arg(info.uchYearHigh).arg(info.uchYearLow);
    QString month = QString("%1").arg(info.uchMonth);
    QString day = QString("%1").arg(info.uchDay);
    QString hour = QString("%1").arg(info.uchHour);
    QString min = QString("%1").arg(info.uchMin);
    QString sec = QString("%1").arg(info.uchSec);

    QString str;
    str = "date -s " + month + "/" + day + "/" + year;
    system(str.toLatin1().data());
    str = "date -s " + hour + ":" + min + ":" + sec;
    system(str.toLatin1().data());
    //强制写入到CMOS
    system("clock -w");

    qDebug()<<"***********************";
    qDebug()<<"date:"<<QDate::currentDate()<<"time:"<<QTime::currentTime();
    qDebug()<<"***********************\n";
}


//获取发送类对象
DDS_Net *NetDevice::dds_sender() const
{
    return ddsNet;
}
