/************************************************************
** 文件名：Reader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：Reader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_READER_H_INCLUDED_
#define _RTPS_READER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Endpoint.h"

//声明
class DataReader;
class HistoryCache;
class RequestScheduler;

class Reader : public Endpoint 
{
public:
    //构造函数
    Reader (_GUID_T Guid,
        const _DATA_READER_QOS* pQos,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        RequestScheduler** pRequestScheduler,
        HistoryCache *pHistoryCache,
        DataReader *pDataReader);

    //析构函数
    ~Reader ();

    //生成_CACHE_CHANGE
    _CACHE_CHANGE *NewChange(_GUID_T WriterGuid, char *pMessage, unsigned long ulLength, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);
    _CACHE_CHANGE *NewChange(_GUID_T WriterGuid, char *pMessage, unsigned long ulLength, _SEQUENCE_NUMBER_T SeqNum, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    //通知DDS DataReader数据到达
    _RETURNCODE_T DataNotify(_SEQUENCE_NUMBER_T LocalSeqNum);

    //获取忽略重复Heartbeat报文的时间
    _DURATION_T HeartbeatSuppressionDuration() 
    {
        return m_HeartbeatSuppressionDuration;
    }

    //获取Heartbeat报文回复延时
    _DURATION_T HearbeatResponseDelay() 
    {
        return m_HeartbeatResponseDelay;
    }

    //获取接收报文的截止期Deadline
    _DURATION_T Deadline() {
        return m_Deadline;
    }

    //初始化调度队列
    virtual _RETURNCODE_T ScheduleListInit() 
    {
        return RETURNCODE_OK;
    }

    //检查是否还有相应的Writer在发送该实例
    //bool noWriters(_INSTANCE_HANDLE_T Handle);

    //获取实例状态
    _RETURNCODE_T GetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind& InstanceState);

	//更新实例状态
	_RETURNCODE_T InstanceUpdate(_GUID_T WriterGuid, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    _SEQUENCE_NUMBER_T GetNewChangeSeqNum() 
    {
        return ++m_LastChangeSeqNum;
    }

    void SetSeqNumNotify(_SEQUENCE_NUMBER_T SeqNum) 
    {
        m_HighestSeqNumNotify = SeqNum;
    }

protected:
    //Heartbeat报文回复延时
    _DURATION_T m_HeartbeatResponseDelay;

    //忽略重复的Heartbeat报文的时间
    _DURATION_T m_HeartbeatSuppressionDuration;

    //接收新报文的截止期
    _DURATION_T m_Deadline;

    //最新生成的Change的序列号
    _SEQUENCE_NUMBER_T m_LastChangeSeqNum;

    //调度队列，0为ImmeditRequestScheduler，1为PeriodRequestScheduler
    RequestScheduler** m_pScheduleList;

    //对应的DDS DataReader
    DataReader *m_pRelatedDataReader;

    //对应的缓冲区
    HistoryCache *m_pReaderCache;

    //保存接收过的实例标识InstanceHandle与instance信息的对应关系
    _INSTANCE_MAP_R m_ReceivedInstance;

    //互斥锁 互斥访问m_ReceivedInstance
#ifdef VXWORKS   //移植
	SEM_ID m_hSemRecvInstMutex;
#else
	HANDLE m_hSemRecvInstMutex;
#endif

    //请求的Deadline未满足的状态
    _REQUESTED_DEADLINE_MISSED_STATUS m_RequestedDeadlineMissedStatus;

    //上交的SequenceNumber
    _SEQUENCE_NUMBER_T m_HighestSeqNumNotify;

	//pQos指针
	//2013-10-12 hjy modify
	_DATA_READER_QOS* m_pQos;
};

#endif
