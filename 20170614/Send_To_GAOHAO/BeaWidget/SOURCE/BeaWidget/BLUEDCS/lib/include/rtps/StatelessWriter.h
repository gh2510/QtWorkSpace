#ifndef _RTPS_STATELESSWRITER_INCLUDED_H
#define _RTPS_STATELESSWRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Writer.h"
#include "rtps/Message.h"

class RequestScheduler;
class ReaderProxy;

class StatelessWriter : public Writer{
public:
    //构造函数
    StatelessWriter(_GUID_T Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList,
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache*     pHistoryCache,
        DataWriter*       pDataWriter,
        RequestScheduler  **pScheduleList);

    //析构函数
    virtual ~StatelessWriter();

    //调度队列初始化
    _RETURNCODE_T ScheduleListInit();

    //添加匹配的订阅端
	_RETURNCODE_T ReaderLocatorAdd( ReaderLocator* pReaderLocator);

    //删除匹配订阅端
    _RETURNCODE_T ReaderLocatorRemove( ReaderLocator* pReaderLocator);

	//查询匹配的订阅端
    ReaderLocator* MatchedLocatorLookup( _GUID_T AReaderGuid );

    //检查是否满足Deadline QoS
    _RETURNCODE_T DeadlineCheck();

    //请求数据发送 被DDSDataWriter调用
    _RETURNCODE_T DataSend(_CACHE_CHANGE *pNewChange);


	//胡敬羽 2013-09-04 修改
	int GetMatchDataReaderNum()
	{
		return m_MatchedLocatorList.size();
	}

    //生成Data报文
    _RETURNCODE_T DataMessageGet( char** pMessage,_MESSAGE_LENGTH_LIST_T* pLengthList, _CACHE_CHANGE *pCacheChange, ReaderLocator *pReaderLocator);

    //生成Data多播报文
    _RETURNCODE_T DataMessageMultiGet(char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList, _CACHE_CHANGE *pSendChange);

    RequestScheduler** GetScheduleList()
	{ 
		return m_pScheduleList;
	}
	_READER_LOCATOR_LIST* GetLocatorList() 
	{ 
		return &m_MatchedLocatorList; 
	}


#ifdef VXWORKS 
	SEM_ID GetMutex() 
	{ 
		return m_hSemMutex; 
	}
#elif WIN32
	HANDLE GetMutex() 
	{ 
		return m_hSemMutex; 
	}
#elif KYLIN
	pthread_mutex_t& GetMutex() 
	{ 
		return m_hSemMutex; 
	}
#endif

    _RETURNCODE_T DataSendFinish(_SEQUENCE_NUMBER_T Seq);

	//是否采取多播
	bool IsMulticast();

	//数据分片
	_RETURNCODE_T DataIntoFrag(char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, _CACHE_CHANGE* pSendChange, _ENTITYID ReaderID);

private:
    
	_READER_LOCATOR_LIST m_MatchedLocatorList;
    //互斥锁 互斥访问对象为Proxy
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
