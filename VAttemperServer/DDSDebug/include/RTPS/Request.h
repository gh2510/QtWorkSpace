/************************************************************
** �ļ�����Request.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Requestͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_REQUEST_H_INCLUDED_
#define _RTPS_REQUEST_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

class Endpoint;
class MessageProcessor;
class MessageTransmitter;

class Request 
{
public:
    Request(
        Endpoint *pEndpoint,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime,
		string strTypeName)
    {
        m_pEndpoint = pEndpoint;
        m_pMessageProcessor = pMessageProcessor;
        m_pMessageTransmitter = pMessageTransmitter;
        m_StartTime = StartTime;
        m_EndTime = EndTime;
		m_strTypeName = strTypeName;
    }

    virtual ~Request() {};

    virtual _RETURNCODE_T Execute() = 0;

    _TIME_T GetStartTime()
    {
        return m_StartTime;
    }

    _TIME_T GetEndTime()
    {
        return m_EndTime;
    }

    Endpoint *GetEndpoint()
    {
        return m_pEndpoint;
    }

public:
    _TIME_T m_StartTime;
    _TIME_T m_EndTime;
	string m_strTypeName;

protected:
    Endpoint *m_pEndpoint;
    MessageProcessor *m_pMessageProcessor;
    MessageTransmitter *m_pMessageTransmitter;
};

#endif
