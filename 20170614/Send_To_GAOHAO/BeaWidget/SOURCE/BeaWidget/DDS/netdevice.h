/************************************************************
** 文件名：netdevice.h
** Copyright (c) 2017 仁谷系统集成
** 创建人：尚超<itshangchao@qq.com>
** 日  期：2017-06-01
** 描  述：netdevice头文件,设备类，增加网络功能
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef NETDEVICE_H
#define NETDEVICE_H

#include <QObject>
#include "DDS/dds_net.h"

class QTimer;

class NetDevice : public QObject
{
    Q_OBJECT
public:
    explicit NetDevice(QObject *parent = 0);
    ~NetDevice();
    static NetDevice *getNetDevice();
    long InitDeviceNet();
    void SendTimeStateInfo(int time);
    void RecvTimeStateInfo(TimeStateInfo info);
    DDS_Net *dds_sender() const;

private:
    DDS_Net *ddsNet; 
    QTimer *timer;

private slots:
    long slot_sendTime();
};

#endif // NETDEVICE_H
