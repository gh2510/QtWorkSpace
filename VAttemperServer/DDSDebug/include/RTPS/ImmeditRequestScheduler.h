/************************************************************
** 文件名：ImmeditRequestScheduler.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-11-14
** 修改人：无
** 日  期：无
** 描  述：ImmeditRequestScheduler头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_IMMEDITREQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_IMMEDITREQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RequestScheduler.h"

#ifdef VXWORKS  //移植
#include <semLib.h>
#else
#include "Windows.h"
#endif


//声明
class MessageProcessor;
class MessageTransmitter;
class Request;

class ImmeditRequestScheduler : public RequestScheduler
{
public:
	ImmeditRequestScheduler(MessageProcessor *pMessageProcessor,
		MessageTransmitter *pMessageTransmitter);
	virtual ~ImmeditRequestScheduler();

	//添加调度请求
	_RETURNCODE_T RequestAdd(Request *pRequest);

	//删除一个调度请求
	_RETURNCODE_T RequestRemove(Request *pRequest);

	//清除由某Endpoint所提出的调度请求
	_RETURNCODE_T RequestClean(Endpoint *pEndpoint);

	//删除调度队列里面与pReaderProxy相关的Request
	_RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy);

	//删除调度队列里面与pWtiterProxy相关的Request
	_RETURNCODE_T RequestClean(WriterProxy *pWriterProxy);

	//进行调度
	_RETURNCODE_T RequestScheduling();

	_RETURNCODE_T RequestLastScheduling();

	//大数据
	bool isBusy();

	//线程/任务入口函数
#ifdef VXWORKS   //移植
	static _RETURNCODE_T ScheduleRun(ImmeditRequestScheduler *pRequestScheduler);
#else
	static DWORD WINAPI ScheduleRun(LPVOID lpRequestScheduler);
#endif

private:
	_RETURNCODE_T RequestExecute(Request *pRequest);

	//计数器信号量 表示RequestScheduler中Request的个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemFull;
#else
	HANDLE m_hSemFull;
#endif
	//计数器信号量 表示RequestScheduler中Request的个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemEmpty;
#else
	HANDLE m_hSemEmpty;
#endif
};
#endif
