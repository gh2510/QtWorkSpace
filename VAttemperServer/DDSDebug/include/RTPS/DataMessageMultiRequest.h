/************************************************************
** �ļ�����DataMessageRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataMessageRequestͷ�ļ�
** ��  ����Version 0.1
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

	//�������DataMessageMultiRequest��endpoint��ͬ����˵�����ԱȽ�
	bool Comparable(DataMessageMultiRequest *pRequest)
    {
		return (this->GetEndpoint() == pRequest->GetEndpoint());
	}

private:
//    ReaderProxy *m_readerProxy;
};

#endif
