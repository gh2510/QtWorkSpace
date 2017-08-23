/************************************************************
** 文件名：ReaderProxy.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-12
** 修改人：无
** 日  期：无
** 描  述：ReaderProxy头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef RTPS_READERPROXY_INCLUDED_H
#define RTPS_READERPROXY_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Message.h"

#ifdef VXWORKS
#include <semLib.h>
#else
#include "Windows.h"
#endif

class StatefulWriter;
class HistoryCache;

class ReaderProxy
{
public:
    //构造函数
    ReaderProxy( _GUID_T ReaderGuid,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        StatefulWriter* pStatefulWriter);

    //析构函数
    virtual ~ReaderProxy();

    //添加_CHANGE_FOR_READER对象
    _CHANGE_FOR_READER* ChangeForReaderAdd( _CACHE_CHANGE* pCacheChange );

    //删除_CHANGE_FOR_READER对象
    _RETURNCODE_T ChangeForReaderRemove( _CACHE_CHANGE* pCacheChange );

    //查找指定的_CHANGE_FOR_READER对象
    _CHANGE_FOR_READER* ChangeForReaderLookup( _SEQUENCE_NUMBER_T SeqNum);

    //获取本ReaderProxy代表的远端订阅端点的GUID
    _GUID_T ReaderGuid();

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

    //设置被确认的Changes
    _RETURNCODE_T AckedChangesSet( _SEQUENCE_NUMBER_T CommittedSeqNum);

    //设置被请求的Changes
    _RETURNCODE_T RequestedChangesSet( _SEQUENCE_NUMBER_SET* pReqSeqNumSet);

    //返回下一次要发送的_CACHE_CHANGE
    _CACHE_CHANGE* NextUnsentChange();

    //返回序列号最小的被请求的_CACHE_CHANGE
    _CACHE_CHANGE* NextRequestedChange();

    //查询指定序列号的_CACHE_CHANGE是否被确认
    bool IsAcked( _SEQUENCE_NUMBER_T SeqNum);

    //查询是否有未确认的_CACHE_CHANGE
    bool UnsentChanges();

    //查询是否有未请求的_CACHE_CHANGE
    bool RequestedChanges();

    //查询是否有未被确认的_CACHE_CHANGE
    bool UnackedChanges();

    //忽略发送过快的AckNack报文
    bool AckNackIgnore( _COUNT_T AckNackCount);

    //返回下次重发Data报文的时间
    _TIME_T NextDataRepairTime();

	//设置重发Data报文的时间
	_RETURNCODE_T SetRepairTime();

	//设置下次可以接收Nack的时间
	_RETURNCODE_T SetNackAllowedTime();

    //设置接收的AckNack报文编号
    _RETURNCODE_T SetAckNackLastCount (_COUNT_T Count) 
    {
        m_AckNackLastCount = Count;

        return RETURNCODE_OK;
    }

    _SEQUENCE_NUMBER_T HighestSeqNumAcked() 
    {
        return m_HighestSeqNumAcked;
    }

    //是否存在多播地址
    bool MulticastExist() 
    {
        if (m_MulticastLocatorList.size() == 0)
            return false;
        return true;
    }

private:
    //远端订阅端点的GUID
    _GUID_T              m_RemoteReaderGuid;

    //对应的StatefulWriter
    StatefulWriter      *m_pRelatedWriter;

    //远端订阅端单播地址列表
    _LOCATOR_LIST_T         m_UnicastLocatorList;

    //远端订阅端多播地址列表
    _LOCATOR_LIST_T         m_MulticastLocatorList;

    //ReaderProxy的_CHANGE_FOR_READER列表
    _CHANGE_FOR_READER_LIST m_ChangesForReaderList;//修改

    //
    bool                m_bIsActive;

    //最近接收到的AckNack报文的序列号
    _COUNT_T             m_AckNackLastCount;

    //已发送_CACHE_CHANGE的最大序列号
    _SEQUENCE_NUMBER_T    m_HighestSeqNumSent;

    //已被确认的_CACHE_CHANGE的最大序列号
    _SEQUENCE_NUMBER_T    m_HighestSeqNumAcked;

    //下一次可以接收Nack的时间
    _TIME_T              m_NextNackAllowedTime;

    //下次重发Data报文的时间
    _TIME_T              m_NextRepairTime;

    //互斥锁 互斥访问m_changesForReader、m_NextRepairTime
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
