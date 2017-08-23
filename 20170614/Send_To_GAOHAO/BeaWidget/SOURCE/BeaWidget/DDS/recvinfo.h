/************************************************************
** 文件名：recvinfo.h
** Copyright (c) 2017 仁谷系统集成
** 创建人：尚超<itshangchao@qq.com>
** 日  期：2017-06-01
** 描  述：recvinfo头文件,订阅主题信息
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef RECVINFO_H
#define RECVINFO_H

#include "DDS_API.h"

class RecvInfo
{
public:
    RecvInfo();
    ~RecvInfo();
    long DDSSubscriber();
    TimeStateInfoDataReader  *TimeStateInfoDataReaderObj;
};

#endif // RECVINFO_H
