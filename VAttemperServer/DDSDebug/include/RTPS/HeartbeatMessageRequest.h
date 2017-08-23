/************************************************************
** 文件名：HeartbeatMessageRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-13
** 修改人：无
** 日  期：无
** 描  述：HeartbeatMessageRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_HEARTBEATMESSAGE_REQUEST_H_INCLUDED_
#define _RTPS_HEARTBEATMESSAGE_REQUEST_H_INCLUDED_

#include "rtps/Request.h"

class HeartbeatMessageRequest : public Request
{
public:
    HeartbeatMessageRequest (Endpoint *pEndpoint,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "Heartbeat") {};

    _RETURNCODE_T Execute();
};

#endif
