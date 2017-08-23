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
#ifndef _RTPS_DATAMESSAGEMULTI_REQUEST_H_INCLUDED_
#define _RTPS_DATAMESSAGEMULTI_REQUEST_H_INCLUDED_

#include "rtps/Request.h"

class ReaderProxy;

class DataMessageMultiRequest : public Request
{
public:
    DataMessageMultiRequest (Endpoint *pEndpoint,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "DataMulti")
    {
//        m_readerProxy = readerProxy;
    };

    _RETURNCODE_T Execute();

	//如果两个DataMessageMultiRequest的endpoint相同，则说明可以比较
	bool Comparable(DataMessageMultiRequest *pRequest)
    {
		return (this->GetEndpoint() == pRequest->GetEndpoint());
	}

private:
//    ReaderProxy *m_readerProxy;
};

#endif
