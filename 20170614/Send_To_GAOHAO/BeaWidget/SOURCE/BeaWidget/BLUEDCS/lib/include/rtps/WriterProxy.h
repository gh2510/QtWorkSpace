/************************************************************
** 文件名：WriterProxy.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：WriterProxy头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_WRITERPROXY_H_INCLUDED_
#define _RTPS_WRITERPROXY_H_INCLUDED_

#include "BasicTypes.h"

#ifdef VXWORKS
#include <semLib.h>
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

class StatefulReader;

class WriterProxy 
{
public:
    //构造函数
    WriterProxy(_GUID_T AWriterGuid,
        StatefulReader *pReader,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList);

    //析构函数
    virtual ~WriterProxy();

private:
    //维护从发布端接收的数据的状态信息
    _RETURNCODE_T ChangeFromWriterAdd(_CHANGE_FROM_WRITER *pChangeFromWriter);
    _RETURNCODE_T ChangeFromWriterRemove(_SEQUENCE_NUMBER_T RemoteSeqNum);

public:
    //获取发布端的GUID
    _GUID_T WriterGuid() 
    {
        return m_RemoteWriterGuid;
    }

    //获取上一次提交数据的时间
    _TIME_T DataNotifyTime() 
    {
        //加互斥锁
#ifdef VXWORKS   //移植
	    semTake(m_hSemMutex, WAIT_FOREVER);
#elif WIN32
    	WaitForSingleObject(m_hSemMutex,INFINITE);
#elif KYLIN
		pthread_mutex_lock(&m_hSemMutex);
#endif

        _TIME_T Temp = m_DataNotifyTime;

        //解互斥锁
#ifdef VXWORKS   //移植
		semGive(m_hSemMutex);
#elif WIN32
		ReleaseMutex(m_hSemMutex);
#elif KYLIN
		pthread_mutex_unlock(&m_hSemMutex);
#endif
        return Temp;
    }

    //获取预定下一次发送AckNack报文的时间
    _TIME_T NextAckNackTime() 
    {
        return m_NextAckNackTime;
    }

    //设置下一次发送AckNack报文的时间
    _RETURNCODE_T NextAckNackTimeSet (_TIME_T Time) 
    {
        m_NextAckNackTime = Time;
        return RETURNCODE_OK;
    }

    //获取单播地址
    _LOCATOR_T UnicastLocatorGet() 
    {
        if (m_UnicastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_UnicastLocatorList[0];
    }

    //获取多播地址
    _LOCATOR_T MulticastLocatorGet() 
    {
        if (m_MulticastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_MulticastLocatorList[0];
    }

    //获取已经成功接收数据序列号，即可以向DDS DataReader提交的数据序列号
    _SEQUENCE_NUMBER_T HaveAvailableChange();

    //忽略发送过快的重复Heartbeat报文
    bool HeartbeatIgnore(_COUNT_T HeartbeatCount);

    //查询是否有数据缺失
    bool MissingChanges();

    //更新数据接收状态
    _RETURNCODE_T ReceivedChangeSet(
        _SEQUENCE_NUMBER_T RemoteSeqNum,
        _SEQUENCE_NUMBER_T LocalSeqNum);

    //更新报文丢失状态
    _RETURNCODE_T LostChangesUpdate(_SEQUENCE_NUMBER_T FirstAvailableSeqNum);

    //更新报文缺失状态
    _RETURNCODE_T MissingChangesUpdate(
        _SEQUENCE_NUMBER_T FirstAvailableSeqNum,
        _SEQUENCE_NUMBER_T LastAvailableSeqNum);

    //更新报文的提交状态
    _RETURNCODE_T NotifyChangesUpdate(_SEQUENCE_NUMBER_T RemoteSeqNum);


    //获取AckNack报文
    _RETURNCODE_T AckNackMessageGet(char **pMessage, unsigned long *pLength);

	//获取m_HighestSeqNumAvailable
	_SEQUENCE_NUMBER_T GetHighestSeqNumAvailable()
    {
		return m_HighestSeqNumAvailable;
	}

    //检查ChangeFromWriterList是否存在RemoteSeqNum的记录
    _SEQUENCE_NUMBER_T ExistChange(_SEQUENCE_NUMBER_T RemoteSeqNum);

	//2013-11-04 hjy modify
	StatefulReader * GetRelatedRTPSReader()
	{
		return m_pRelatedReader;
	}

private:
    //远端发布端的GUID
    _GUID_T m_RemoteWriterGuid;

    //对应的订阅端
    StatefulReader *m_pRelatedReader;

    //单播地址列表
    _LOCATOR_LIST_T m_UnicastLocatorList;

    //多播地址列表
    _LOCATOR_LIST_T m_MulticastLocatorList;

    //从发布端接收的数据 状态列表
    _CHANGE_FROM_WRITER_LIST_T m_ChangesFromWriter;

    //下一次允许接收重复Heartbeat报文的时间
    _TIME_T m_NextHeartbeatAllowedTime;

    //上一次向DDS DataReader提交数据的时间
    _TIME_T m_DataNotifyTime;

    //下一次发送AckNack报文的时间（响应Heartbeat）
    _TIME_T m_NextAckNackTime;

    //最近的一次接收的Heartbeat报文序号
    _COUNT_T m_HeartbeatLastCount;

    //下一次发送AckNack的序号
    _COUNT_T m_AcknowledgedStatusCount;

    //可以向DDS DataReader提交的最大序列号
    _SEQUENCE_NUMBER_T m_HighestSeqNumAvailable;

    //已经向DDS DataReader提交的数据的最大序列号
    _SEQUENCE_NUMBER_T m_HighestSeqnumNotify;

	//2014-02-28 hjy modify 计数发送的Ack报文,每50次输出一次,然后清零
	unsigned long SendAckCount;

    //互斥锁 互斥访问m_ChangesFromWriter、m_HighestSeqNumAvailable、m_DataNotifyTime
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
