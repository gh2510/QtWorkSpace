/************************************************************
** �ļ�����SubscribeManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����SubscribeManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _SUBSCRIBEMANAGER_H
#define _SUBSCRIBEMANAGER_H
#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/Topic.h"
#include <string>

#include "TopicInfoDataReader.h"
#include "NodeInfoDataReader.h"
#include "CompInfoDataReader.h"
#include "RecordInfoSendListDataReader.h"

#include "TopicInfoDRListener.h"
#include "NodeInfoDRListener.h"
#include "CompInfoDRListener.h"
#include "RecordInfoSendListDRListener.h"
#include "DynamicDRListener.h"

#ifdef VXWORKS
class DynamicDataReader;
#else
#include "DynamicDataReader.h"
#endif

class DomainParticipant;
class InfoProcessor;
class Topic;

struct _DOMAIN_PARTICIPANT_T
{
	Topic* pNodeInfo;
	Topic* pCompInfo;
	Topic* pTopicInfo;
	Topic* pRecordInfo;
	DomainParticipant* pDDSParticipant;
	DataReader* pNodeInfoDataReader;
	DataReader* pCompInfoDataReader;
	DataReader* pTopicInfoDataReader;
	DataReader* pRecordInfoSendListDataReader;
	DataReaderListener* pNodeInfoDRListener;
	DataReaderListener* pCompInfoDRListener;
	DataReaderListener* pTopicInfoDRListener;
	DataReaderListener* pRecordInfoSendListDRListener;
	list<DynamicDataReader*> DynamicDataReaderList;
};

typedef list<_DOMAIN_PARTICIPANT_T*> _DOMAIN_PARTICIPANT_LIST_T;
typedef list<_DOMAIN_PARTICIPANT_T*> _MONITOR_DOMAIN_PARTICIPANT_LIST;
typedef list<_DOMAIN_PARTICIPANT_T*> _RECORD_DOMAIN_PARTICIPANT_LIST;

class SubscribeManager
{
public:
	SubscribeManager(InfoProcessor* pInfoProcessor);               //SubscribeManager.h
	~SubscribeManager();           //SubscribeManager.h

	//DomainParticipant�б�
	_MONITOR_DOMAIN_PARTICIPANT_LIST m_DDSParticipantMonitorList;
	_RECORD_DOMAIN_PARTICIPANT_LIST m_DDSParticipantRecordList;
	//��̬���������б�
	_TOPIC_LIST_T DynamicTopicList;
	list<string> m_TopicRecordName;

private:
	//������ָ��
	InfoProcessor* m_pProcessor;

public:
	_RETURNCODE_T StartMonitorSubManager(list<unsigned long> DomainIDList);     //SubscribeManager.h
	_RETURNCODE_T StartRecordSubManager(list<unsigned long> DomainIDList);    //SubscribeManager.h

	_RETURNCODE_T ReleaseMonitorSubManager();  //SubscribeManager.h
	_RETURNCODE_T ReleaseRecordSubManager();  //SubscribeManager.h
	
	Topic* CreateDynamicTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);  //SubscribeManager.h
	_RETURNCODE_T CreateDynamicDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);  //SubscribeManager.h
	
	_RETURNCODE_T DeleteDynamicTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);  //SubscribeManager.h
	_RETURNCODE_T DeleteDynamicDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);  //SubscribeManager.h

	_RETURNCODE_T GetRecordTopic(list<string> TopicRecordName);  //SubscribeManager.h
	bool IsTopicRecord(string strTopicName);  //SubscribeManager.h

	//���ddsDomainParticipant��_DOMAIN_PARTICIPANT_Tָ�룬������ģ�鴴����̬�����ߵ���
	_DOMAIN_PARTICIPANT_T* GetRelatedDomainParticipant_t(DomainParticipant* pDomianParticipant);  //SubscribeManager.h

private:
	Topic* CreateNodeInfoTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	Topic* CreateCompInfoTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	Topic* CreateTopicInfoTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	Topic* CreateRecordInfoSendListTopic(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h

	_RETURNCODE_T CreateNodeInfoDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	_RETURNCODE_T CreateCompInfoDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	_RETURNCODE_T CreateTopicInfoDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
	_RETURNCODE_T CreateRecordInfoSendListDR(_DOMAIN_PARTICIPANT_T* pDomainParticipant);  //SubscribeManager.h
};

#endif
