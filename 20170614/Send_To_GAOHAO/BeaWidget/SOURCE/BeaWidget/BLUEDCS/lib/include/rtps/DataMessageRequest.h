/************************************************************
** 文件名：DataMessageRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-13
** 修改人：无
** 日  期：无
** 描  述：DataMessageRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_DATAMESSAGE_REQUEST_H_INCLUDED_
#define _RTPS_DATAMESSAGE_REQUEST_H_INCLUDED_

#include "rtps/Request.h"

class ReaderProxy;

class DataMessageRequest : public Request
{
public:
    DataMessageRequest (Endpoint *pEndpoint,
        ReaderProxy *pReaderProxy,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "Data")
    {
        m_pReaderProxy = pReaderProxy;
    };

    _RETURNCODE_T Execute();

	//如果两个DataMessageRequest的endpoint、readerproxy都相同，则表明它们是可比较的
	bool Comparable(DataMessageRequest *pRequest)
    {
		return (this->GetEndpoint() == pRequest->GetEndpoint() && this->m_pReaderProxy == pRequest->m_pReaderProxy);
	}

	ReaderProxy* GetReaderProxy()
    {
		return m_pReaderProxy;
	}

private:
    ReaderProxy *m_pReaderProxy;
};

#endif
