/************************************************************
** �ļ�����TimerManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-11-14
** �޸��ˣ���
** ��  �ڣ���
** ��  ����TimerManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _TIMERMANAGER_H_
#define _TIMERMANAGER_H_

#include <list>
#include <iostream>
#include "rtps/PeriodRequestScheduler.h"
#include "rtps/Request.h"

#ifdef VXWORKS
#include "vxWorks.h"
#include "time.h"
#include "semLib.h"
typedef map<timer_t, Request*> _TIMER_TO_REQUEST;
#else
#include "windows.h"
//wparamΪVOTE_ID VOTE_TIME, lparamΪITimer
#define START_TIMER_MSG WM_USER+1
//wparamΪTimer id
#define END_TIMER_MSG	WM_USER+2
//���ȴ�ʱ��
#define MAX_WAIT_TIME	2000

typedef map<int, Request*> _TIMER_TO_REQUEST;
#endif

using namespace std;

class TimerManager
{
private:

#ifdef VXWORKS
	_TIMER_TO_REQUEST m_IdITimer;
	//list<timer_t> m_timerList;
	//��ʱ����ID��
	timer_t m_iTimerId;
#else
	_TIMER_TO_REQUEST m_IdITimer;
	//list<int> m_timerList;
	int m_iTimerId;

	HANDLE m_hSemMutex;
	//������GetMessage�������߳�ID����PostThreadMessage��ʹ��
	DWORD m_dwThreadId;
	HANDLE m_hThreadHandle;
	//���ڱ���GetMessage�߳����ڵ���StartTimer���߳�����
	HANDLE m_hSchedulerRun;
	//�õ�������TimerId
	HANDLE m_hEventGetTimerId;

protected:
	void CreateSchedulerThread();
	static void _stdcall TimerProc(HWND hwnd, UINT uMsg, UINT uEvent, DWORD dwTimer);
	static DWORD _stdcall SchedulerThread(LPVOID lpVoid);
#endif

	PeriodRequestScheduler *m_pRelatedRequestScheduler;


public:
	TimerManager(PeriodRequestScheduler *pRequestScheduler);
	~TimerManager();

#ifdef VXWORKS
	//������ʱ�����ɹ�����1��ʧ�ܷ���0,modeΪ0����ִֻ��һ�Σ�1������sec:ulNsecΪ����ִ��
	int StartTimer(long lNsec, long lSec, Request *pRequest, int iMode);
	//ɾ����ʱ�����ɹ�����1��ʧ�ܷ���0
	int DeleteTimer(timer_t Timer);
	//����Timer����Request
	Request* GetRequest(timer_t Timer);
	//����Request����Timer
	timer_t GetTimer(Request* pRequest);
#else
	//������ʱ�����ɹ�����1��ʧ�ܷ���0,modeΪ0����ִֻ��һ�Σ�1������iMillisecΪ����ִ��
	int StartTimer(int iMilliSec,Request *pRequest, int iMode);
	//ɾ����ʱ�����ɹ�����1��ʧ�ܷ���0
	int DeleteTimer(int iTimer);
	//����Timer����Request
	Request* GetRequest(int iTimer);
	//����Request����Timer
	int GetTimer(Request* pRequest);
#endif
	
};

#endif
