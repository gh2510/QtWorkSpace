/************************************************************
** �ļ�����FragRepairRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-10-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����FragRepairRequestͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_FRAGREPAIR_REQUEST_H_INCLUDED_
#define _RTPS_FRAGREPAIR_REQUEST_H_INCLUDED_

#include "rtps/Request.h"
#include "rtps/Message.h"

class ReaderProxy;

class FragRepairRequest : public Request 
{
public:
	FragRepairRequest (Endpoint *pEndpoint,
		ReaderProxy *pReaderProxy,
		_SEQUENCE_NUMBER *pWriterSN,
		_FRAGMENT_NUMBER_SET *pFragmentNumberSet,
		MessageProcessor *pMessageProcessor,
		MessageTransmitter *pMessageTransmitter,
		_TIME_T StartTime,
		_TIME_T EndTime) :
	Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "FragRepair")
    {
		m_pReaderProxy = pReaderProxy;
		m_pWriterSN = *pWriterSN;
		m_pFragmentNumberSet = *pFragmentNumberSet;
	};

	_RETURNCODE_T Execute();

	//�������FragRepairRequest��endpoint��readerproxy����ͬ������������ǿɱȽϵ�
	bool Comparable(FragRepairRequest *pRequest)
    {
		//		return (this->GetEndpoint() == request->GetEndpoint() && this->m_readerProxy == request->m_readerProxy);
		return (this->GetEndpoint() == pRequest->GetEndpoint());
	}

	ReaderProxy* GetReaderProxy()
    {
		return m_pReaderProxy;
	}

private:
	ReaderProxy *m_pReaderProxy;
	_SEQUENCE_NUMBER m_pWriterSN;
	_FRAGMENT_NUMBER_SET m_pFragmentNumberSet;
};

#endif
