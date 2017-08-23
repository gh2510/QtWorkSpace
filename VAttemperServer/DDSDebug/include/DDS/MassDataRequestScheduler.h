//大数据
/************************************************************
** 文件名：MassDataRequestSchedule.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2013-07-24
** 修改人：无
** 日  期：无
** 描  述：MassDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREQUESTEDSCHEDULER_H_INCLUDED_
#define _DDS_MASSDATAREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "DDS/MassDataRequest.h"
#include "DDS/DomainParticipant.h"

#ifdef VXWORKS  //移植
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

    //添加调度请求
    _RETURNCODE_T RequestAdd(MassDataRequest *pRequest);

    //删除一个调度请求
    _RETURNCODE_T RequestRemove(MassDataRequest *pRequest);

	_RETURNCODE_T RequestScheduling();

	//线程/任务入口函数
#ifdef VXWORKS   //移植
	static _RETURNCODE_T ScheduleRun(MassDataRequestScheduler *pRequestScheduler);
#else
	static DWORD WINAPI ScheduleRun(LPVOID lpRequestScheduler);
#endif

protected:
    //调度队列
    _MASSDATA_REQUEST_LIST_T m_RequestList;
	DomainParticipant *m_RelatedDomainParticipant;

    //互斥信号量
#ifdef VXWORKS   //移植
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
