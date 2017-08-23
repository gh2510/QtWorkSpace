/************************************************************
** 文件名：Writer.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-12
** 修改人：无
** 日  期：无
** 描  述：DataWriter头文件
** 版  本：Writer 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_WRITER_INCLUDED_H
#define _RTPS_WRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/endpoint.h"

#ifdef VXWORKS
#include <semLib.h>
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

class HistoryCache;
class RequestScheduler;
class DataWriter;

class Writer : public Endpoint
{
public:
    //构造函数
    Writer( _GUID_T            Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList, 
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache      *pHistoryCache, 
        DataWriter        *pDataWriter,
        RequestScheduler  **pScheduleList );

    //析构函数
    virtual ~Writer();

    //生成一个_CACHE_CHANGE
    _CACHE_CHANGE* NewChange(char *pData, int iLength, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    //获取Writer的信息
    //_WRITER_PROXY_DATA* getWriterInfo();
    //virtual HistoryCache* GetWriterCache();
    //virtual _DURATION_T* GetNackResponseDelay();
    //virtual RequestScheduler* GetScheduleList();

    //将数据发送请求插入请求队列 虚函数 提供接口
    virtual _RETURNCODE_T DataSend(_CACHE_CHANGE *pCache) 
    {
        return RETURNCODE_OK;
    };

    virtual _RETURNCODE_T DataSendFindish() 
    {
        return RETURNCODE_OK;
    }

    //返回对应的缓冲区指针
    HistoryCache* GetWriterCache() 
    {
        return m_pWriterCache;
    }

    //获取发送新报文的截止期
    _TIME_T Deadline() 
    {
        //cout<<"get Deadline:"<<m_Deadline.lSecond<<"|"<<m_Deadline.ulNanosec<<endl;
        return m_Deadline;
    }

    //获取Heartbeat报文发送周期
    _DURATION_T HeartbeatPeriod() 
    {
        return m_HeartbeatPeriod;
    }

    //发送结束
    virtual _RETURNCODE_T DataSendFinish() 
    {
        return RETURNCODE_OK;
    }

    //初始化调度队列
    virtual _RETURNCODE_T ScheduleListInit() 
    {
        return RETURNCODE_OK;
    }

    _DURATION_T GetNackResponseDelay() 
    {
        return m_NackResponseDelay;
    };

    _DURATION_T GetNackSuppressionDuration() 
    {
        return m_NackSuppressionDuration;
    };

    virtual _RETURNCODE_T SetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind InstanceState);

	RequestScheduler** Request_Scheduler() 
    {
		return m_pScheduleList;
	}

	DataWriter* GetRelatedDW() 
    {
		return m_pRelatedDataWriter;
	}

	//2014-02-27 hjy modify 互斥访问m_HighestSeqNumFinished
#ifdef VXWORKS   //移植
	SEM_ID m_hCacheMutex;
#elif WIN32
	HANDLE m_hCacheMutex;
#elif KYLIN
	pthread_mutex_t m_hCacheMutex;
#endif

protected:
    //Writer发送模式
    bool             m_bPushMode;

    //Heartbeat发送周期
    _DURATION_T       m_HeartbeatPeriod;

    //回复Nack报文的延时
    _DURATION_T       m_NackResponseDelay;

    //忽略一段时间内的重复Nack报文
    _DURATION_T       m_NackSuppressionDuration;

    //上一次发送报文的时间
    _TIME_T           m_DataSendTime;

    //发送新报文的截止期
    _DURATION_T       m_Deadline;

    //上一次生成的Change的序列号
    _SEQUENCE_NUMBER_T m_LastChangeSequence;

    //已经成功发送的Change的序列号
    _SEQUENCE_NUMBER_T m_HighestSeqNumFinished;

    //对应的DDS DataWriter
    DataWriter       *m_pRelatedDataWriter;

    //对应的缓冲区
    HistoryCache     *m_pWriterCache;

    //调度队列，0为ImmeditRequestScheduler，1为PeriodRequestScheduler
    RequestScheduler **m_pScheduleList;

    //互斥锁 互斥访问m_DataSendTime
#ifdef VXWORKS   //移植
	SEM_ID m_hSemTimeMutex;
#elif WIN32
	HANDLE m_hSemTimeMutex;
#elif KYLIN
	pthread_mutex_t m_hSemTimeMutex;
	int _sem_init_time_ret;
#endif

    //保存发送过的实例标识InstanceHandle与instance信息的对应关系
    _INSTANCE_MAP_W m_SentInstance;

    //提供的Deadline未满足的状态
    _OFFERED_DEADLINE_MISSED_STATUS m_OfferedDeadlineMissedStatus;

	//pQos指针
	//2013-10-12 hjy modify
	_DATA_WRITER_QOS* m_pQos;
};

#endif
