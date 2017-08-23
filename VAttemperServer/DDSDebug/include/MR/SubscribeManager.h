/************************************************************
** 文件名：SubscribeManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：SubscribeManager头文件
** 版  本：Version 0.1
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

	//DomainParticipant列表
	_MONITOR_DOMAIN_PARTICIPANT_LIST m_DDSParticipantMonitorList;
	_RECORD_DOMAIN_PARTICIPANT_LIST m_DDSParticipantRecordList;
	//动态订阅主题列表
	_TOPIC_LIST_T DynamicTopicList;
	list<string> m_TopicRecordName;

private:
	//处理器指针
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

	//获得ddsDomainParticipant的_DOMAIN_PARTICIPANT_T指针，被发现模块创建动态订阅者调用
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
