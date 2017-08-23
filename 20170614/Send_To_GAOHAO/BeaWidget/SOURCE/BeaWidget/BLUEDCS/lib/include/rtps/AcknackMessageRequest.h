/************************************************************
** 文件名：AcknackMessageRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-13
** 修改人：无
** 日  期：无
** 描  述：AcknackMessageRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_ACKNACKMESSAGE_REQUEST_H_INCLUDED_
#define _RTPS_ACKNACKMESSAGE_REQUEST_H_INCLUDED_

#include "rtps/Request.h"

class WriterProxy;
class MessageProcessor;
class MessageTransmitter;

class AcknackMessageRequest : public Request
{
public:
    AcknackMessageRequest (Endpoint *pEndpoint,
        WriterProxy *pWriterProxy,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "Acknack")
    {
        m_pWriterProxy = pWriterProxy;
    };

    _RETURNCODE_T Execute();

	WriterProxy* GetWriterProxy()
    {
		return m_pWriterProxy;
	}

private:
    WriterProxy *m_pWriterProxy;
};

#endif
