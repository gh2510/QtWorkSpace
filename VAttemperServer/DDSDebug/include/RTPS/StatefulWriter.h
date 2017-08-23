/************************************************************
** 文件名：StatefulWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-12
** 修改人：无
** 日  期：无
** 描  述：StatefulWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_STATEFULWRITER_INCLUDED_H
#define _RTPS_STATEFULWRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Writer.h"
#include "rtps/Message.h"

class RequestScheduler;
class ReaderProxy;

class StatefulWriter : public Writer
{
public:
    //构造函数
    StatefulWriter(_GUID_T Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList,
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache*     pHistoryCache,
        DataWriter*       pDataWriter,
        RequestScheduler  **pScheduleList);

    //析构函数
    virtual ~StatefulWriter();

    //调度队列初始化
    _RETURNCODE_T ScheduleListInit();

    //添加匹配的订阅端代理
    _RETURNCODE_T MatchedReaderAdd( ReaderProxy* pReaderProxy);

    //删除匹配的订阅端代理
    _RETURNCODE_T MatchedReaderRemove( ReaderProxy* pReaderProxy);

    //删除特定前缀的订阅端代理
    //_RETURNCODE_T MatchedReaderRemove(_GUID_PREFIX_T GuidPrefix);

	//胡敬羽 2013-09-04 修改
	int GetMatchDataReaderNum()
	{
		return m_MatchedReaderList.size();
	}

	//胡敬羽 2013-09-04 获取互斥锁
#ifdef VXWORKS 
	SEM_ID GetMutex() 
	{ 
		return m_hProxySemMutex; 
	}
#else
	HANDLE GetMutex() 
	{ 
		return m_hProxySemMutex; 
	}
#endif

    //查询匹配的订阅端代理
    ReaderProxy* MatchedReaderLookup( _GUID_T AReaderGuid);

    //查询数据是否被所有订阅端确认
    bool IsAckedByAll( _SEQUENCE_NUMBER_T SequenceNumber);

    //查询是否需要向订阅端发送Heartbeat
    bool NeedHeartbeat(ReaderProxy *pReaderProxy);

    //获取Heartbeat报文的目的端 即ReaderProxy（未接收到所有数据）
    _RETURNCODE_T HeartbeatDestGet(_READER_PROXY_LIST &List);

    //检查是否满足Deadline QoS
    _RETURNCODE_T DeadlineCheck();

    //请求数据发送 被DDSDataWriter调用
    _RETURNCODE_T DataSend(_CACHE_CHANGE *pNewChange);

    //生成Heartbeat报文
    _RETURNCODE_T HeartbeatMessageGet( char** pMessage, unsigned long *pLength, ReaderProxy *pReaderProxy);

    //生成Data报文
    _RETURNCODE_T DataMessageGet( char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList, ReaderProxy* pReaderProxy);

    //生成Data多播报文
    _RETURNCODE_T DataMessageMultiGet(char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList);

    //接收AckNack报文
    _RETURNCODE_T AckNackMessageReceive( _ACKNACK_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    RequestScheduler** GetScheduleList()
    { 
        return m_pScheduleList;
    }

    _RETURNCODE_T DataSendFinish();

	//是否采取多播
	bool IsMulticast();

	//数据分片
	_RETURNCODE_T DataIntoFrag(char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, _CACHE_CHANGE* pSendChange, _ENTITYID ReaderID);

	//数据分片修复
	_RETURNCODE_T FragRepairMessageGet( char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, ReaderProxy* pReaderProxy, _SEQUENCE_NUMBER_T WriterSN, _FRAGMENT_NUMBER_SET _FRAGMENT_NUMBER_SET);

	//接收NackFrag报文
	_RETURNCODE_T NackFragMessageReceive( _NACK_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

private:
    //匹配的订阅端代理列表
    _READER_PROXY_LIST m_MatchedReaderList; //修改

	//2014-02-28 hjy modify 计数发送的HeartBeat报文,每50次输出一次,然后清零
	unsigned long SendHeartbeatCount;

	//2014-02-28 hjy modify 计数接收到ack的报文个数,每50次输出一次,然后清零
	/*unsigned long ReceiveAckCount;*/


    //互斥锁 互斥访问对象为Proxy
#ifdef VXWORKS   //移植
	SEM_ID m_hProxySemMutex;
#else
	HANDLE m_hProxySemMutex;
#endif

    //互斥锁 互斥访问对象为DataMessageGet
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMsgGetMutex;
#else
	HANDLE m_hSemMsgGetMutex;
#endif

	//互斥锁 互斥访问对象为historycache
#ifdef VXWORKS   //移植
	SEM_ID m_hSemCacheMutex;
#else
	HANDLE m_hSemCacheMutex;
#endif

	//互斥锁 互斥访问对象为DataMessageGet
//#ifdef VXWORKS   //移植
//	SEM_ID m_hSemHistoryCacheMutex;
//#else
//	HANDLE m_hSemHistoryCacheMutex;
//#endif
};

#endif
