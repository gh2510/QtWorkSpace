/************************************************************
** �ļ�����PeriodRequestScheduler.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-11-14
** �޸��ˣ���
** ��  �ڣ���
** ��  ����PeriodRequestSchedulerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PERIODREQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_PERIODREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RequestScheduler.h"

#ifdef VXWORKS  //��ֲ
#include <semLib.h>
#include "time.h"
#else
#include "Windows.h"
#endif

//����
class MessageProcessor;
class MessageTransmitter;
class Request;
class TimerManager;

class PeriodRequestScheduler : public RequestScheduler
{
public:
	PeriodRequestScheduler(MessageProcessor *pMessageProcessor,
		MessageTransmitter *pMessageTransmitter);
	virtual ~PeriodRequestScheduler();

	//��ӵ�������
	_RETURNCODE_T RequestAdd(Request *pRequest);

	//ɾ��һ����������
	_RETURNCODE_T RequestRemove(Request *pRequest);

	//�����ĳEndpoint������ĵ�������
	_RETURNCODE_T RequestClean(Endpoint *pEndpoint);

	//ɾ�����ȶ���������readerProxy��ص�Request
	_RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy);

	//ɾ�����ȶ���������wtiterProxy��ص�Request
	_RETURNCODE_T RequestClean(WriterProxy *pWriterProxy);

	TimerManager* GetTimerManager()
    {
		return m_pTimerManager;
	}

	//���m_RequestList�Ƿ������Ӧrequest
	bool RequestExist(Request *pRequest);

#ifdef VXWORKS   //��ֲ
	static void TimeRoutine(timer_t Timer, int iPoint);
#else
	static void TimeRoutine(int iTimer, PeriodRequestScheduler* pRequestScheduler);
#endif

private:
	//_RETURNCODE_T RequestExecute(Request *pRequest);

	TimerManager *m_pTimerManager;
};
#endif
