/************************************************************
** �ļ�����AcknackMessageRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����AcknackMessageRequestͷ�ļ�
** ��  ����Version 0.1
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
