/************************************************************
** 文件名：sendinfo.h
** Copyright (c) 2017 仁谷系统集成
** 创建人：尚超<itshangchao@qq.com>
** 日  期：2017-06-01
** 描  述：sendinfo头文件,发布主题信息
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef SENDINFO_H
#define SENDINFO_H

#include "DDS_API.h"

class SendInfo
{
public:
    SendInfo();
    long DDSPublisher();

    TimeStateInfoDataWriter *TimeStateInfoDataWriterObj;
    DataWriter *TimeStateInfodataWriter;
};

#endif // SENDINFO_H
