/************************************************************
** 文件名：DeadlineRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-13
** 修改人：无
** 日  期：无
** 描  述：DeadlineRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_DEADLINE_REQUEST_H_INCLUDED_
#define _RTPS_DEADLINE_REQUEST_H_INCLUDED_

#include "rtps/Request.h"

class DeadlineRequest : public Request
{
public:
    DeadlineRequest (Endpoint *pEndpoint,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "Deadline")
    {
    };

    _RETURNCODE_T Execute();
};

#endif
