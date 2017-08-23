/************************************************************
** �ļ�����ImmeditRequestScheduler.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-11-14
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ImmeditRequestSchedulerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_IMMEDITREQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_IMMEDITREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RequestScheduler.h"

#ifdef VXWORKS  //��ֲ
#include <semLib.h>
#else
#include "Windows.h"
#endif


//����
class MessageProcessor;
class MessageTransmitter;
class Request;

class ImmeditRequestScheduler : public RequestScheduler
{
public:
	ImmeditRequestScheduler(MessageProcessor *pMessageProcessor,
		MessageTransmitter *pMessageTransmitter);
	virtual ~ImmeditRequestScheduler();

	//��ӵ�������
	_RETURNCODE_T RequestAdd(Request *pRequest);

	//ɾ��һ����������
	_RETURNCODE_T RequestRemove(Request *pRequest);

	//�����ĳEndpoint������ĵ�������
	_RETURNCODE_T RequestClean(Endpoint *pEndpoint);

	//ɾ�����ȶ���������pReaderProxy��ص�Request
	_RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy);

	//ɾ�����ȶ���������pWtiterProxy��ص�Request
	_RETURNCODE_T RequestClean(WriterProxy *pWriterProxy);

	//���е���
	_RETURNCODE_T RequestScheduling();

	_RETURNCODE_T RequestLastScheduling();

	//������
	bool isBusy();

	//�߳�/������ں���
#ifdef VXWORKS   //��ֲ
	static _RETURNCODE_T ScheduleRun(ImmeditRequestScheduler *pRequestScheduler);
#else
	static DWORD WINAPI ScheduleRun(LPVOID lpRequestScheduler);
#endif

private:
	_RETURNCODE_T RequestExecute(Request *pRequest);

	//�������ź��� ��ʾRequestScheduler��Request�ĸ���
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemFull;
#else
	HANDLE m_hSemFull;
#endif
	//�������ź��� ��ʾRequestScheduler��Request�ĸ���
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemEmpty;
#else
	HANDLE m_hSemEmpty;
#endif
};
#endif
