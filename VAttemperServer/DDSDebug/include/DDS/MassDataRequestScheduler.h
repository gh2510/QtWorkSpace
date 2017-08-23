//������
/************************************************************
** �ļ�����MassDataRequestSchedule.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2013-07-24
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MassDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREQUESTEDSCHEDULER_H_INCLUDED_
#define _DDS_MASSDATAREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "DDS/MassDataRequest.h"
#include "DDS/DomainParticipant.h"

#ifdef VXWORKS  //��ֲ
#include <semLib.h>
#else
#include "Windows.h"
#endif

#define SCHEDULER_LENGTH 10000

class MassDataRequestScheduler
{
public:
    MassDataRequestScheduler(DomainParticipant* pDomainParticipant);
	virtual ~MassDataRequestScheduler();

    //��ӵ�������
    _RETURNCODE_T RequestAdd(MassDataRequest *pRequest);

    //ɾ��һ����������
    _RETURNCODE_T RequestRemove(MassDataRequest *pRequest);

	_RETURNCODE_T RequestScheduling();

	//�߳�/������ں���
#ifdef VXWORKS   //��ֲ
	static _RETURNCODE_T ScheduleRun(MassDataRequestScheduler *pRequestScheduler);
#else
	static DWORD WINAPI ScheduleRun(LPVOID lpRequestScheduler);
#endif

protected:
    //���ȶ���
    _MASSDATA_REQUEST_LIST_T m_RequestList;
	DomainParticipant *m_RelatedDomainParticipant;

    //�����ź���
#ifdef VXWORKS   //��ֲ
	 SEM_ID m_hSemMutex;
	 SEM_ID m_hSemEmpty;
	 SEM_ID m_hSemFull;
#else
	 HANDLE m_hSemMutex;
	 HANDLE m_hSemEmpty;
	 HANDLE m_hSemFull;
#endif

};

#endif
