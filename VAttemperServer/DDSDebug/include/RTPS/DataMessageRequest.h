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

	//�������DataMessageRequest��endpoint��readerproxy����ͬ������������ǿɱȽϵ�
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
