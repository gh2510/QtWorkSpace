/************************************************************
** �ļ�����DeadlineRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DeadlineRequestͷ�ļ�
** ��  ����Version 0.1
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
