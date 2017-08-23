/************************************************************
** 文件名：TimerManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-11-14
** 修改人：无
** 日  期：无
** 描  述：TimerManager头文件
** 版  本：Version 0.1
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
//wparam为VOTE_ID VOTE_TIME, lparam为ITimer
#define START_TIMER_MSG WM_USER+1
//wparam为Timer id
#define END_TIMER_MSG	WM_USER+2
//最大等待时间
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
	//定时器的ID号
	timer_t m_iTimerId;
#else
	_TIMER_TO_REQUEST m_IdITimer;
	//list<int> m_timerList;
	int m_iTimerId;

	HANDLE m_hSemMutex;
	//阻塞在GetMessage函数的线程ID，在PostThreadMessage中使用
	DWORD m_dwThreadId;
	HANDLE m_hThreadHandle;
	//用于保护GetMessage线程先于调用StartTimer的线程运行
	HANDLE m_hSchedulerRun;
	//得到并返回TimerId
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
	//启动定时器，成功返回1，失败返回0,mode为0代表只执行一次，1代表以sec:ulNsec为周期执行
	int StartTimer(long lNsec, long lSec, Request *pRequest, int iMode);
	//删除定时器，成功返回1；失败返回0
	int DeleteTimer(timer_t Timer);
	//根据Timer查找Request
	Request* GetRequest(timer_t Timer);
	//根据Request查找Timer
	timer_t GetTimer(Request* pRequest);
#else
	//启动定时器，成功返回1；失败返回0,mode为0代表只执行一次，1代表以iMillisec为周期执行
	int StartTimer(int iMilliSec,Request *pRequest, int iMode);
	//删除定时器，成功返回1；失败返回0
	int DeleteTimer(int iTimer);
	//根据Timer查找Request
	Request* GetRequest(int iTimer);
	//根据Request查找Timer
	int GetTimer(Request* pRequest);
#endif
	
};

#endif
