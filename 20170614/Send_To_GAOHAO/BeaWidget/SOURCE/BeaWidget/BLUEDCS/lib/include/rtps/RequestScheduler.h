/************************************************************
** 文件名：RequestScheduler.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-13
** 修改人：无
** 日  期：无
** 描  述：RequestScheduler头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_REQUESTEDSCHEDULER_H_INCLUDED_
#define _RTPS_REQUESTEDSCHEDULER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
#include <semLib.h>
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

#define SCHEDULER_LENGTH 10000

//声明
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

    //添加调度请求
    virtual _RETURNCODE_T RequestAdd(Request *pRequest) = 0;

    //删除一个调度请求
    virtual _RETURNCODE_T RequestRemove(Request *pRequest) = 0;

    //清除由某Endpoint所提出的调度请求
    virtual _RETURNCODE_T RequestClean(Endpoint *pEndpoint) = 0;

	//删除调度队列里面与readerProxy相关的Request
	virtual _RETURNCODE_T RequestClean(ReaderProxy *pReaderProxy) = 0;

	//删除调度队列里面与wtiterProxy相关的Request
	virtual _RETURNCODE_T RequestClean(WriterProxy *pWriterProxy) = 0;

    //进行调度
    //_RETURNCODE_T RequestScheduling();

    //线程/任务入口函数
//#ifdef VXWORKS   //移植
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
    //报文处理端
    MessageProcessor *m_pMessageProcessor;
    MessageTransmitter *m_pMessageTransmitter;
    //调度队列
    _REQUEST_LIST_T m_RequestList;

    //互斥信号量
#ifdef VXWORKS   //移植
	 SEM_ID m_hSemMutex;
#elif WIN32
	 HANDLE m_hSemMutex;
#elif KYLIN
	 pthread_mutex_t m_hSemMutex;
	 int _sem_init_ret;
#endif

};

#endif
