/************************************************************
** 文件名：PeriodRequestScheduler.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-11-14
** 修改人：无
** 日  期：无
** 描  述：PeriodRequestScheduler头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PERIODREQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_PERIODREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RequestScheduler.h"

#ifdef VXWORKS  //移植
#include <semLib.h>
#include "time.h"
#else
#include "Windows.h"
#endif

//声明
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

	//添加调度请求
	_RETURNCODE_T RequestAdd(Request *pRequest);

	//删除一个调度请求
	_RETURNCODE_T RequestRemove(Request *pRequest);

	//清除由某Endpoint所提出的调度请求
	_RETURNCODE_T RequestClean(Endpoint *pEndpoint);

	//删除调度队列里面与readerProxy相关的Request
	_RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy);

	//删除调度队列里面与wtiterProxy相关的Request
	_RETURNCODE_T RequestClean(WriterProxy *pWriterProxy);

	TimerManager* GetTimerManager()
    {
		return m_pTimerManager;
	}

	//检查m_RequestList是否存在相应request
	bool RequestExist(Request *pRequest);

#ifdef VXWORKS   //移植
	static void TimeRoutine(timer_t Timer, int iPoint);
#else
	static void TimeRoutine(int iTimer, PeriodRequestScheduler* pRequestScheduler);
#endif

private:
	//_RETURNCODE_T RequestExecute(Request *pRequest);

	TimerManager *m_pTimerManager;
};
#endif
