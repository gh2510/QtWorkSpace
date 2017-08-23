/************************************************************
** 文件名：SubscriptionsDataManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-22
** 修改人：无
** 日  期：无
** 描  述：SubscriptionsDataManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_SUBSCRIPTIONSDATAMANAGER_H_INCLUDED_
#define _RTPS_SUBSCRIPTIONSDATAMANAGER_H_INCLUDED_
#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS
#include <taskLib.h>
#include <sysLib.h>
#include <sockLib.h>
#elif WIN32
#include "windows.h"
#include <time.h>
#elif KYLIN
//include something
#endif

class DomainParticipant;
class DataWriter;
class Participant;

class SubscriptionsDataManager
{
public:
    SubscriptionsDataManager(DomainParticipant *pDomainParticipant);

    virtual ~SubscriptionsDataManager();

    //判断是否是新的DataReader
    bool IsNewDataReader(_DISCOVERED_READER_DATA *pData);

    //配置ReaderProxy
    //接收到一个远端DataReader的新建信息，将其与本地所有的DataWriter匹配，建立ReaderProxy
    _RETURNCODE_T ReaderProxyConfigure(
        _DISCOVERED_READER_DATA* pData);

    //配置ReaderProxy
    //本地新建了一个DataWriter，将其与所有远端的DataReader信息匹配，建立ReaderProxy
    _RETURNCODE_T ReaderProxyConfigure(
        DataWriter* pDataWriter);

    //删除ReaderProxy
    //接收到远端的DataReader的删除信息，在本地所有DataWriter的ReaderProxy中寻找其信息，删除
    _RETURNCODE_T ReaderProxyRemove(
        _DISCOVERED_READER_DATA* pData);

    //增加
    _RETURNCODE_T AddRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteDataReader(_SUBSCRIPTIONS_DATA_LIST_T::iterator itData);
    //更新
    _RETURNCODE_T RefreshRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //更新
    _RETURNCODE_T RefreshRemoteDataReader(
        _DISCOVERED_READER_DATA *pData1,
        _DISCOVERED_READER_DATA *pData2);

    //远端的Participant超时 删除其下所有DataReader
    _RETURNCODE_T RemoteParticipantTimeout(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

	//返回远端发布信息列表
	_SUBSCRIPTIONS_DATA_LIST_T RemoteSubscriptionsList() 
    {
		return m_pRemoteSubscriptionsList;
	}

	//测试发布订阅匹配时间专用 返回匹配Discovery主题的DataReader个数  2013-09-09 胡敬羽
	unsigned long GetDiscoveryMatchDataReaderNumber()
	{
		return m_DiscoveryMatchDataReaderNumber;
	}

	//测试发布订阅匹配时间专用 增加匹配Discovery主题的DataReader个数  2013-09-09 胡敬羽
	void AddDiscoveryMatchDataReaderNumber()
	{
		m_DiscoveryMatchDataReaderNumber++;
	}

	//测试发布订阅匹配时间专用 设定匹配Discovery主题的DataReader总个数  2013-09-09 胡敬羽
	void SetDiscoveryMatchTotalDataReaderNumber(unsigned long TotalNumber)
	{
		m_DiscoveryMatchTotalDataReaderNumber = TotalNumber;
	}

	//测试发布订阅匹配时间专用 返回匹配Discovery主题的DataReader总个数  2013-09-09 胡敬羽
	unsigned long GetDiscoveryMatchTotalDataReaderNumber()
	{
		return m_DiscoveryMatchTotalDataReaderNumber;
	}

#ifdef VXWORKS
		//测试发布订阅匹配时间专用 创建DataWriter之前时间  2013-09-09 胡敬羽
		void SetDiscoveryBeginTime()
		{
			clock_gettime(CLOCK_REALTIME, &m_DiscoveryBeginTime);
		}

		//测试发布订阅匹配时间专用 设置收到N个DataReader之后的时间  2013-09-09 胡敬羽
		void SetDiscoveryEndTime()
		{
			clock_gettime(CLOCK_REALTIME, &m_DiscoveryEndTime);
		}
		
		//测试发布订阅匹配时间专用 返回收到N个DataReader之后的时间  2013-09-09 胡敬羽
		double GetDiscoveryTime()
		{
			return (double)(m_DiscoveryEndTime.tv_sec + m_DiscoveryEndTime.tv_nsec*0.000000001 - m_DiscoveryBeginTime.tv_sec - m_DiscoveryBeginTime.tv_nsec*0.000000001 );
		}
#else
		//测试发布订阅匹配时间专用 创建DataWriter之前时间  2013-09-09 胡敬羽
		void SetDiscoveryBeginTime()
		{
			//QueryPerformanceCounter(&m_DiscoveryBeginTime);
		}

		//测试发布订阅匹配时间专用 设置收到N个DataReader之后的时间  2013-09-09 胡敬羽
		void SetDiscoveryEndTime()
		{
			//QueryPerformanceFrequency(&m_DiscoveryFrequence);
			//QueryPerformanceCounter(&m_DiscoveryEndTime);
		}
		
		//测试发布订阅匹配时间专用 返回收到N个DataReader之后的时间  2013-09-09 胡敬羽
		double GetDiscoveryTime()
		{
			return 0;
			//return (double)(m_DiscoveryEndTime.QuadPart-m_DiscoveryBeginTime.QuadPart)/(double)m_DiscoveryFrequence.QuadPart;
		}
#endif
	

private:
    //属于的DomainParticipant
    DomainParticipant *m_pDomainParticipant;
    //远端DataReader信息链表
    _SUBSCRIPTIONS_DATA_LIST_T m_pRemoteSubscriptionsList;

    //查找
    _SUBSCRIPTIONS_DATA_LIST_T::iterator LookupRemoteDataReader(
        _DISCOVERED_READER_DATA *pData);

    //判断是否是同一个DataReader
    bool IsSameDataReader(
        _DISCOVERED_READER_DATA *pData1,
        _DISCOVERED_READER_DATA *pData2);

    //为DataWriter做匹配 配置ReaderProxy
    bool MatchDataWriter(
        DataWriter *pDataWriter,
        _DISCOVERED_READER_DATA *pData);

    //判断DataReader是否属于Participant
    bool Belong(_DISCOVERED_READER_DATA *pReaderData,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pParticipantData);
	bool Belong(_DISCOVERED_READER_DATA *pReaderData,
        Participant *aParticipant);
	
#ifdef VXWORKS
		//测试发布订阅匹配时间专用 创建DataWriter之前时间戳  2013-09-09 胡敬羽
		struct timespec m_DiscoveryBeginTime;

		//测试发布订阅匹配时间专用 收到N个DataReader之后时间戳  2013-09-09 胡敬羽
		struct timespec m_DiscoveryEndTime;

#else
		//测试发布订阅匹配时间专用 创建DataWriter之前时间戳  2013-09-09 胡敬羽
		//LARGE_INTEGER m_DiscoveryBeginTime;

		//测试发布订阅匹配时间专用 收到N个DataReader之后时间戳  2013-09-09 胡敬羽
		//LARGE_INTEGER m_DiscoveryEndTime;

		//测试发布订阅匹配时间专用 收到N个DataReader之后时间戳  2013-09-09 胡敬羽
		//LARGE_INTEGER m_DiscoveryFrequence;

#endif
	
	//测试发布订阅匹配时间专用 匹配Discovery主题的DataReader个数  2013-09-09 胡敬羽
	unsigned long m_DiscoveryMatchDataReaderNumber;

	//测试发布订阅匹配时间专用 匹配Discovery主题的DataReader的总个数  2013-09-09 胡敬羽
	unsigned long m_DiscoveryMatchTotalDataReaderNumber;


    //互斥锁
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
