/************************************************************
** �ļ�����DomainParticipant.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����DomainParticipantͷ�ļ�
** ��  ����Version 0.1
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
//������
class MassDataRequestScheduler;

#pragma warning(disable:4251)

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DomainParticipant : public Entity{
#else
class DDS_DLL DomainParticipant : public Entity
{
#endif

private:
    //��ID
    unsigned long m_ulDomainId;
    //DomainParticipant��ID
    unsigned long m_ulDomainParticipantId;

    //����������list <Publisher*>
    _PUBLISHER_LIST_T m_PublisherList;
    //����������list <Subscriber*>
    _SUBSCRIBER_LIST_T m_SubscriberList;

    //���ӦParticipant����
    Participant* m_pRelatedParticipant;
    //���Ӧ�ķ��ֶ���
    Discovery* m_pRelatedDiscovery;

    //Ĭ�ϻ�������С
    unsigned long m_ulDefaultCacheLength;
    //Ĭ�Ϸ�������������
    unsigned long m_ulMaxPublisher;
    //Ĭ�Ϸ�������������
    unsigned long m_ulMaxSubscriber;
    //Ĭ��������������
    unsigned long m_ulMaxTopic;
    //�����߼���
    unsigned long m_ulCountPublisher;
    //�����߼���
    unsigned long m_ulCountSubscriber;
    //�������
    unsigned long m_ulCountTopic;
    //Ĭ��QoS
    _ENTITY_QOS m_DefaultQoS;

    //Ĭ�Ϸ�������������
    unsigned long m_ulMaxDatawriter;
    //Ĭ�϶��Ķ���������
    unsigned long m_ulMaxDatareader;

    //�Ѿ����������ö˵�
    _BUILTIN_ENDPOINT_SET_T m_BuiltinEndpoint;
    //��������list <Topic*>
    _TOPIC_LIST_T m_TopicList;
	//���ݹ�����������list <ContentFilteredTopic*>
    _CONTENT_FILTERED_TOPIC_LIST_T m_ContentfilteredtopicList;
    //������������list <_TYPE*>
    _TYPE_LIST_T m_RegisteredTypeList;
	//�������ͺ�TypeCode��Ӧ��ϵ
	_TYPE_CODE_LIST_T m_TypecodeList;
    //Ĭ��IP��ַ����
    _IP_LIST_T  m_DefaultIpList;

    _DURATION_T m_ResendPeriod;

    //ϵͳʱ��
    //_TIME_T m_time;

    //�Ƿ�ʹ�öಥ
    bool m_bUseMulticast;
    
    //�ಥ��ַ��Χ����
    unsigned long m_ulMulticastAddressLow;
    
    //�ಥ��ַ����
    unsigned long m_ulMulticastAddressNumber;

	//�Ƿ�ʹ�öಥ�ڵ㷢��
    bool m_bUseMulticastDiscovery;
    
    //���ڽڵ㷢�ֵĶಥ��ַ
    unsigned long m_ulMulticastAddress;

	//2015-3-17 hjy add MultiNetworkCard
	bool m_bUseMultiNetworkCard;
	int m_iMultiNetworkCardCount;

	//2015-3-17 hjy add MultiNetworkCard for 9 network cards at most
	unsigned long m_ulMultiNetworkCardAddress[9];
	unsigned long m_ulMultiNetworkCardPortLow;

	//2015-3-18 hjy add:check multi network card IP address in the ddsconfig.conf is right or not
	unsigned long m_ulTotalNetworkCardAddress[9];

	//��أ�1��ʾ��أ�0��ʾ�������
	int m_iMonitor;
	//��¼��1��ʾ��¼��0��ʾ������¼
	int m_iRecord;
	//�����
	char* m_pCompName;
	//��ؼ�¼����
	MonitorRecordAgent* m_pAgent;
	//recordserver��ʼΪ0��ʾ����¼,1Ϊ��¼.
	int m_iRecordServerStatus;

	//��������ָ��
	PublicationsDataManager* m_pPublicationManager;

	//���Ĺ���ָ��
	SubscriptionsDataManager* m_pSubscriptionManager;	//������ 2013-09-09 ���Է�������ƥ��ʱ�����

	//��ʷ�����ռ�����ָ��
	HistoricGatherManager* m_pHistoricManager;

	//������
	MassDataRequestScheduler *m_pScheduler;

	//local broadcast address
	string m_sLocalBroadcastAddr;

	//������
#ifdef VXWORKS   //��ֲ
    //���������߳�/����
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

    //���캯��
    DomainParticipant(unsigned long ulDomainId,
        unsigned long ulDomainParticipantId, char* pCompName);
    //��������
    virtual ~DomainParticipant();

    //���������
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
    
	//������
	bool isBusy();
	_RETURNCODE_T RequestAdd(MassDataRequest *pRequest);
    //_SPDP_DISCOVERED_PARTICIPANT_DATA* getSPDPdiscoveredParticipantData();
    //_DISCOVERED_WRITER_DATA* getDiscoveredWriterData(DataWriter* dataWriter,entityStatus writerStatus);
    //_DISCOVERED_READER_DATA* getDiscoveredReaderData(DataReader* dataReader,entityStatus readStatus);

	//��ؼ�¼��غ���
	//��ȡ��ؼ�¼ָ��
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
	//�ı��Ƿ񱾻���Ϊ��¼��������־
	_RETURNCODE_T ChangeRecordStatus(int iRecordstatus)
    {
		m_iRecordServerStatus = iRecordstatus;
		return RETURNCODE_OK;
	}
	//��ȡ������Ϊ��¼��������־
	int GetRecordStatus()
    {
		return m_iRecordServerStatus;
	}

	_RETURNCODE_T SetPublicationsDataManeger(PublicationsDataManager* pPubDataManager)
    {
		m_pPublicationManager = pPubDataManager;
		return RETURNCODE_OK;
	}

	//������ 2013-09-09 ���Է�������ƥ��ʱ�����
	_RETURNCODE_T SetSubscriptionsDataManeger(SubscriptionsDataManager* pSubDataManager)
	{
		m_pSubscriptionManager = pSubDataManager;
		return RETURNCODE_OK;
	}

	PublicationsDataManager* GetPublicationsDataManeger()
    {
		return m_pPublicationManager;
	}

	//������ 2013-09-09 ���Է�������ƥ��ʱ�����
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
