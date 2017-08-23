/************************************************************
** 文件名：dds_net.h
** Copyright (c) 2017 仁谷系统集成
** 创建人：尚超<itshangchao@qq.com>
** 日  期：2017-06-01
** 描  述：dds_net头文件，集中处理DDS网络相关事件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef DDS_NET_H
#define DDS_NET_H

#include "DDS/recvinfo.h"
#include "DDS/sendinfo.h"

class DDS_Net
{
public:
    DDS_Net();
    ~DDS_Net();
    long InitDDSNet();
    void ReleaseDDSNet();
    _RETURNCODE_T sendTimeStateInfo(TimeStateInfo info);

private:
    RecvInfo *ddsRecv;
    SendInfo *ddsSend;
};

#endif // DDS_NET_H
