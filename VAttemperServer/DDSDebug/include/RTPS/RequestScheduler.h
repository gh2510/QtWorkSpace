/************************************************************
** �ļ�����RequestScheduler.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����RequestSchedulerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_REQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_REQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
#include <semLib.h>
#else
#include "Windows.h"
#endif

#define SCHEDULER_LENGTH 10000

//����
class MessageProcessor;
class MessageTransmitter;
class Request;
class WriterProxy;
class ReaderProxy;

class RequestScheduler
{
public:
    RequestScheduler(MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter);
	virtual ~RequestScheduler();

    //��ӵ�������
    virtual _RETURNCODE_T RequestAdd(Request *pRequest) = 0;

    //ɾ��һ����������
    virtual _RETURNCODE_T RequestRemove(Request *pRequest) = 0;

    //�����ĳEndpoint������ĵ�������
    virtual _RETURNCODE_T RequestClean(Endpoint *pEndpoint) = 0;

	//ɾ�����ȶ���������readerProxy��ص�Request
	virtual _RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy) = 0;

	//ɾ�����ȶ���������wtiterProxy��ص�Request
	virtual _RETURNCODE_T RequestClean(WriterProxy *pWriterProxy) = 0;

    //���е���
    //_RETURNCODE_T RequestScheduling();

    //�߳�/������ں���
//#ifdef VXWORKS   //��ֲ
//    static _RETURNCODE_T ScheduleRun(RequestScheduler *requestScheduler);
//#else
//	static DWORD WINAPI ScheduleRun(LPVOID requestScheduler);
//#endif

    MessageProcessor *GetMessageProcessor()
    {
        return m_pMessageProcessor;
    }

    MessageTransmitter *GetMessageTransmitter ()
    {
        return m_pMessageTransmitter;
    }

//private:
//    virtual _RETURNCODE_T RequestExecute(Request *pRequest) = 0;

protected:
    //���Ĵ����
    MessageProcessor *m_pMessageProcessor;
    MessageTransmitter *m_pMessageTransmitter;
    //���ȶ���
    _REQUEST_LIST_T m_RequestList;

    //�����ź���
#ifdef VXWORKS   //��ֲ
	 SEM_ID m_hSemMutex;
#else
	 HANDLE m_hSemMutex;
#endif

};

#endif
