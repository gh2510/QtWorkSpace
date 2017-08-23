/************************************************************
** 文件名：StatefulReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：StatefulReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_STATEFULREADER_H_INCLUDED_
#define _RTPS_STATEFULREADER_H_INCLUDED_

#include "BasicTypes.h"
#include "rtps/Reader.h"
#include "rtps/Message.h"

class WriterProxy;
class RequestScheduler;

class StatefulReader : public Reader 
{
public:
    //构造函数
    StatefulReader (
        _GUID_T Guid,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        const _DATA_READER_QOS* pQos,
        RequestScheduler** pRequestScheduler,
        DataReader *pDataReader,
        HistoryCache *pHistoryCache);

    //析构函数
    virtual ~StatefulReader ();

    //调度队列初始化
    _RETURNCODE_T ScheduleListInit();

    //增加匹配的发布端代理
    _RETURNCODE_T MatchedWriterAdd (WriterProxy *pWriterProxy);

    //删除匹配的发布端代理
    _RETURNCODE_T MatchedWriterRemove (WriterProxy *pWriterProxy);

    //删除特定前缀的发布端代理
    //_RETURNCODE_T MatchedWriterRemove (_GUID_PREFIX_T GuidPrefix);

    //查询匹配的发布端代理
    WriterProxy *MatchedWriterLookup (_GUID_T Guid);

    //检查Deadline QoS是否满足
    _RETURNCODE_T DeadlineCheck ();

    //接收Data报文
    _RETURNCODE_T DataMessageReceive (_DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

	//接收DataFrag报文
	_RETURNCODE_T DataFragMessageReceive(_DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    //接收Heartbeat报文
    _RETURNCODE_T HeartbeatMessageReceive (_HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    //生成AckNack报文
    _RETURNCODE_T AckNackMessageGet (char **pMessage, unsigned long *ulLength, WriterProxy *writerProxy);

    //检查m_MatchedWriter中是否存在特定writerProxy
    bool WriterProxyExist (_GUID_T WriterGUID);

	//返回数据分片列表长度
	unsigned long FragmentDataListSizeGet() 
    {
		return m_FragmentDataList.size();
	}

	//检查特定序号的数据分片接收状态
	_RETURNCODE_T FragNumberSetGet(_GUID_T WriterGuid, _SEQUENCE_NUMBER_T MissingNum, _FRAGMENT_NUMBER_SET* pFragNackState);

	//匹配的发布者个数
	unsigned long MatchedWriterNum()
    {
		return m_MatchedWriter.size();
	}

	RequestScheduler** GetRequestScheduler() 
    {
		return m_pScheduleList;
	}

	//2013-11-04 hjy modify
	//返回互斥锁 互斥访问对象为m_MatchedWriter
#ifdef VXWORKS   //移植
	SEM_ID GetStatefulReaderMutex()
	{
		return m_hSemMutex;
	}
#elif WIN32
	HANDLE GetStatefulReaderMutex()
	{
		return m_hSemMutex;
	}
#elif KYLIN
	pthread_mutex_t& GetStatefulReaderMutex()
	{
		return m_hSemMutex;
	}
#endif

private:
    //远端Writer代理列表
    _WRITER_PROXY_LIST_T m_MatchedWriter;

	//数据分片列表
	_FRAGMENT_DATA_LIST_T m_FragmentDataList;

	//接收新报文的截止期
    _DURATION_T m_FragDeadline;

    //互斥锁 互斥访问对象为Proxy
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#elif WIN32
	HANDLE m_hSemMutex;
#elif KYLIN
	pthread_mutex_t m_hSemMutex;
	int _sem_init_ret;
#endif

	//数据分片锁
#ifdef VXWORKS   //移植
	SEM_ID m_hSemFragMutex;
#elif WIN32
	HANDLE m_hSemFragMutex;
#elif KYLIN
	pthread_mutex_t m_hSemFragMutex;
	int _sem_init_frag_ret;
#endif

};

#endif
