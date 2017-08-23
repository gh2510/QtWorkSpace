/************************************************************
** 文件名：DomainParticipant.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 描  述：DomainParticipant头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_DOMAIN_PARTICIPANT_H_
#define _DDS_DOMAIN_PARTICIPANT_H_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "RTPS/Discovery.h"
#include "RTPS/Participant.h"
#include "DDS/CReadConfig.h"
#include "DDS/Entity.h"
#include "mr/MonitorRecordAgent.h"
#include "Durability/HistoricGatherManager.h"

class Participant;
class Discovery;
class Publisher;
class Entity;//2013-10-14 hjy modify
class Subscriber;
class Topic;
class TopicDescription;
class ContentFilteredTopic;
class DataWriter;
class DataReader;
class DataReaderListener;
class DataWriterListener;
class Agent;
class PublicationsDataManager;
class SubscriptionsDataManager;
//大数据
class MassDataRequestScheduler;

#pragma warning(disable:4251)

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DomainParticipant : public Entity{
#else
class DDS_DLL DomainParticipant : public Entity
{
#endif

private:
    //域ID
    unsigned long m_ulDomainId;
    //DomainParticipant的ID
    unsigned long m_ulDomainParticipantId;

    //发布者链表，list <Publisher*>
    _PUBLISHER_LIST_T m_PublisherList;
    //订阅者链表，list <Subscriber*>
    _SUBSCRIBER_LIST_T m_SubscriberList;

    //相对应Participant对象
    Participant* m_pRelatedParticipant;
    //相对应的发现对象
    Discovery* m_pRelatedDiscovery;

    //默认缓冲区大小
    unsigned long m_ulDefaultCacheLength;
    //默认发布者上限数量
    unsigned long m_ulMaxPublisher;
    //默认发布者上限数量
    unsigned long m_ulMaxSubscriber;
    //默认主题上限数量
    unsigned long m_ulMaxTopic;
    //发布者计数
    unsigned long m_ulCountPublisher;
    //订阅者计数
    unsigned long m_ulCountSubscriber;
    //主题计数
    unsigned long m_ulCountTopic;
    //默认QoS
    _ENTITY_QOS m_DefaultQoS;

    //默认发布端上限数量
    unsigned long m_ulMaxDatawriter;
    //默认订阅端上限数量
    unsigned long m_ulMaxDatareader;

    //已经创建的内置端点
    _BUILTIN_ENDPOINT_SET_T m_BuiltinEndpoint;
    //主题链表，list <Topic*>
    _TOPIC_LIST_T m_TopicList;
	//数据过滤主题链表，list <ContentFilteredTopic*>
    _CONTENT_FILTERED_TOPIC_LIST_T m_ContentfilteredtopicList;
    //主题类型链表，list <_TYPE*>
    _TYPE_LIST_T m_RegisteredTypeList;
	//主题类型和TypeCode对应关系
	_TYPE_CODE_LIST_T m_TypecodeList;
    //默认IP地址链表
    _IP_LIST_T  m_DefaultIpList;

    _DURATION_T m_ResendPeriod;

    //系统时间
    //_TIME_T m_time;

    //是否使用多播
    bool m_bUseMulticast;
    
    //多播地址范围下限
    unsigned long m_ulMulticastAddressLow;
    
    //多播地址个数
    unsigned long m_ulMulticastAddressNumber;

	//是否使用多播节点发现
    bool m_bUseMulticastDiscovery;
    
    //用于节点发现的多播地址
    unsigned long m_ulMulticastAddress;

	//2015-3-17 hjy add MultiNetworkCard
	bool m_bUseMultiNetworkCard;
	int m_iMultiNetworkCardCount;

	//2015-3-17 hjy add MultiNetworkCard for 9 network cards at most
	unsigned long m_ulMultiNetworkCardAddress[9];
	unsigned long m_ulMultiNetworkCardPortLow;

	//2015-3-18 hjy add:check multi network card IP address in the ddsconfig.conf is right or not
	unsigned long m_ulTotalNetworkCardAddress[9];

	//监控，1表示监控，0表示不被监控
	int m_iMonitor;
	//记录，1表示记录，0表示不被记录
	int m_iRecord;
	//组件名
	char* m_pCompName;
	//监控记录代理
	MonitorRecordAgent* m_pAgent;
	//recordserver初始为0表示不记录,1为记录.
	int m_iRecordServerStatus;

	//发布管理指针
	PublicationsDataManager* m_pPublicationManager;

	//订阅管理指针
	SubscriptionsDataManager* m_pSubscriptionManager;	//胡敬羽 2013-09-09 测试发布订阅匹配时间添加

	//历史数据收集管理指针
	HistoricGatherManager* m_pHistoricManager;

	//大数据
	MassDataRequestScheduler *m_pScheduler;

	//local broadcast address
	string m_sLocalBroadcastAddr;

	//大数据
#ifdef VXWORKS   //移植
    //启动发送线程/任务
    int SendTaskStart();
#else
	HANDLE SendTaskStart();
#endif

public:

#ifdef VXWORKS   
	SEM_ID m_hSemTopicWMutex;
#else
	HANDLE m_hSemTopicWMutex;
#endif

    //构造函数
    DomainParticipant(unsigned long ulDomainId,
        unsigned long ulDomainParticipantId, char* pCompName);
    //析构函数
    virtual ~DomainParticipant();

    //配置项加载
    _RETURNCODE_T Config();

    _RETURNCODE_T TimeInitialize(void);
    _RETURNCODE_T BuiltinEndpointInitialize(void);

    unsigned long GetDomainId(void) 
    {
        return m_ulDomainId;
    }
    unsigned long GetDomainParticipantId(void) 
    {
        return m_ulDomainParticipantId;
    }

    Publisher* CreatePublisher();
    _RETURNCODE_T DeletePublisher(Publisher* pPublisher);

    Subscriber* CreateSubscriber();
    _RETURNCODE_T DeleteSubscriber(Subscriber* pSubscriber);

    Topic* CreateTopic(string strTopicName, string strTypeName);
    _RETURNCODE_T DeleteTopic(Topic* pTopic);
    Topic* FindTopic(string strTopicName);

	ContentFilteredTopic* Create_ContentFilteredTopic(string strTopicName, const string strFilter_expression, 
												      Topic* pRelated_topic, _STRING_SEQ Parameters);
    _RETURNCODE_T Delete_ContentFilteredTopic(ContentFilteredTopic* pTopic);
    ContentFilteredTopic* Find_ContentFilteredTopic(string strTopicName);

    _RETURNCODE_T DeleteContainedEntities(void);
	_RETURNCODE_T DeleteBuildinEntities(void);//2013-10-14 hjy modify

    _RETURNCODE_T InsertRegisteredType(Agent *pAgent);
    Agent* LookupRegisteredType(string strTypeName);

	_RETURNCODE_T InsertRegisteredTypeCode(TypeCode *pTypeCode, string strTypeName);
	TypeCode *LookupRegisteredTypeCode(string strTypeName);

    static _TIME_T DDSGetCurrentTime(void);

    _PUBLISHER_LIST_T FindPublishers(void);
    _SUBSCRIBER_LIST_T FindSubscribers(void);

    DataWriter* CreateDataWriter(Topic* pTopic,
        DataWriterListener* pListener,
        const _DATA_WRITER_QOS* pQos,
        _STATUS_MASK Mask);
    DataReader* CreateDataReader(TopicDescription* pTopic,
        DataReaderListener* pListener,
        const _DATA_READER_QOS* pQos,
        _STATUS_MASK Mask);

    _RETURNCODE_T Delete_Datawriter(DataWriter * pDatawriter);

    _RETURNCODE_T Delete_Datareader(DataReader * pDatareader );

    Participant* GetRelatedParticipant(void) 
    {
        return m_pRelatedParticipant;
    }
    Discovery* GetRelatedDiscovery(void) 
    {
        return m_pRelatedDiscovery;
    }
    _ENTITY_QOS GetDefaultQos(void) 
    {
        return m_DefaultQoS;
    }

    _BUILTIN_ENDPOINT_SET_T BuiltinEndpointGet() 
    {
        return m_BuiltinEndpoint;
    }

    _RETURNCODE_T BuiltinEndpointSet(_BUILTIN_ENDPOINT_SET_T AvailableBuiltinEndpoint) 
    {
        m_BuiltinEndpoint = AvailableBuiltinEndpoint;
        return RETURNCODE_OK;
    }

    _TOPIC_LIST_T GetTopicList()
    {
        return m_TopicList;
    }

    _TYPE_LIST_T GetRegisteredTypeList()
    {
        return m_RegisteredTypeList;
    }

    _IP_LIST_T  GetDefaultIpList()
    {
        return m_DefaultIpList;
    }

    unsigned long GetIpAddress()
    {
        return *m_DefaultIpList.begin();
    }


	//2015-3-17 hjy add MultiNetworkCard
	unsigned long GetMultiNetworkCardAddress(int i)
	{
		return m_ulMultiNetworkCardAddress[i];
	}

	bool isMultiNetworkCard()
	{
		return m_bUseMultiNetworkCard;
	}

	int GetMultiNetworkCardCount()
	{
		return m_iMultiNetworkCardCount;
	}

	void SetMultiNetworkCardPort(unsigned long portNumber)
	{
		m_ulMultiNetworkCardPortLow = portNumber;
	}

	unsigned long GetMultiNetworkCardPort()
	{
		return m_ulMultiNetworkCardPortLow;
	}
	//end of 2015-3-17 hjy add MultiNetworkCard

    bool IsMulticast()
    {
        return m_bUseMulticast;
    }
    
    unsigned long GetMultiAddrLow()
    {
        return m_ulMulticastAddressLow;
    }
    
    unsigned long GetMultiAddrNumber()
    {
        return m_ulMulticastAddressNumber;
    }
    
	//大数据
	bool isBusy();
	_RETURNCODE_T RequestAdd(MassDataRequest *pRequest);
    //_SPDP_DISCOVERED_PARTICIPANT_DATA* getSPDPdiscoveredParticipantData();
    //_DISCOVERED_WRITER_DATA* getDiscoveredWriterData(DataWriter* dataWriter,entityStatus writerStatus);
    //_DISCOVERED_READER_DATA* getDiscoveredReaderData(DataReader* dataReader,entityStatus readStatus);

	//监控记录相关函数
	//获取监控记录指针
	char* GetCompName()
    {
		return m_pCompName;
	}
	MonitorRecordAgent* GetMonitorRecordAgent()
    {
		return m_pAgent;
	}
	int GetMonitorAgent()
    {
		return m_iMonitor;
	}
	int GetRecordAgent()
    {
		return m_iRecord;
	}
	//改变是否本机作为记录服务器标志
	_RETURNCODE_T ChangeRecordStatus(int iRecordstatus)
    {
		m_iRecordServerStatus = iRecordstatus;
		return RETURNCODE_OK;
	}
	//获取本机作为记录服务器标志
	int GetRecordStatus()
    {
		return m_iRecordServerStatus;
	}

	_RETURNCODE_T SetPublicationsDataManeger(PublicationsDataManager* pPubDataManager)
    {
		m_pPublicationManager = pPubDataManager;
		return RETURNCODE_OK;
	}

	//胡敬羽 2013-09-09 测试发布订阅匹配时间添加
	_RETURNCODE_T SetSubscriptionsDataManeger(SubscriptionsDataManager* pSubDataManager)
	{
		m_pSubscriptionManager = pSubDataManager;
		return RETURNCODE_OK;
	}

	PublicationsDataManager* GetPublicationsDataManeger()
    {
		return m_pPublicationManager;
	}

	//胡敬羽 2013-09-09 测试发布订阅匹配时间添加
	SubscriptionsDataManager* GetSubscriptionsDataManeger()
	{
		return m_pSubscriptionManager;
	}

	HistoricGatherManager* GetHistoricGatherManager()
    {
		return m_pHistoricManager;
	}

	DWORD FindProcess(char *pStrProcessName);
	string GetLocalBroadcastAddress()
	{
		return m_sLocalBroadcastAddr;
	}
};

#endif
