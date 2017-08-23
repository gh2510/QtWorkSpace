/************************************************************
** 文件名：MonitorRecordAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-07-26
** 修改人：无
** 日  期：无
** 描  述：MonitorRecordAgent头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef MonitorRecordAgent_hh
#define MonitorRecordAgent_hh
#include"MRBasicTypes.h"
#include "MRReturnCode.h"

#ifdef VXWORKS 
#include <semLib.h>
#else
#include "Windows.h" 
#endif

#include "string"
using std::string;
class DomainParticipant;
class NodePublishManager;
class CompPublishManager;
class TopicPublishManager;
class RecordPublishManager;
class LocalDataGather;

#ifdef VXWORKS
class MonitorRecordAgent 
{
private:
	//DomainParticipant指针
	DomainParticipant *m_pDDSParticipant;
	//本地信息搜集器指针
	LocalDataGather *m_pLocalDataGather;
	//节点状态信息发布管理器指针
	NodePublishManager *m_pNodePublicationManager;
	//组件状态信息发布器指针
	CompPublishManager *m_pCompPublicationManager;
	//信息状态信息发布器指针
	TopicPublishManager *m_pTopicPublicationManager;
	//数据状态信息发布器指针
	RecordPublishManager *m_pRedordPublicationManager;

	//节点状态信息
	_NODE_INFO* m_pNodeInfo;
	//组件状态信息
	_COMP_INFO* m_pCompInfo;

	//互斥锁
	SEM_ID m_hSemNodeInfoMutex;
	SEM_ID m_hSemCompInfoMutex;
	SEM_ID m_hSemTopicInfoMutex;
	SEM_ID m_hSemRecordInfoMutex;

public:
	//记录发送线程
 	int m_hRecordSendTaskId;

	//构造函数,启动监控或记录
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, int iTaskId, char* pCompName, int iMONITOR, int iRECORD);    //MonitorRecordAgent.h
	//析构函数
	~MonitorRecordAgent (void);	
	//初始化函数，启动监控和记录
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, int iTaskId,char* pCompName);    //MonitorRecordAgent.h
	//初始化函数，启动监控
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, int iTaskId,char* pCompName);   //MonitorRecordAgent.h


	//初始化函数，启动
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);   //MonitorRecordAgent.h

	//获取DomainParticipant指针
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}      //MonitorRecordAgent.h

	//发送节点状态信息
	_RETURNCODE_T  SendNodeInfo(void);       //MonitorRecordAgent.h
	//发送组件状态信息
	_RETURNCODE_T SendCompInfo(void);        //MonitorRecordAgent.h
	//发送信息流状态信息
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);     //MonitorRecordAgent.h
	//发送数据状态信息
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);  //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();      //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();         //MonitorRecordAgent.h

};

#else

#ifdef _DDS_LIB_FILE

class MonitorRecordAgent
{
private:
	//DomainParticipant指针
	DomainParticipant *m_pDDSParticipant;
	//本地信息搜集器指针
	LocalDataGather *m_pLocalDataGather;
	//节点状态信息发布管理器指针
	NodePublishManager *m_pNodePublicationManager;
	//组件状态信息发布器指针
	CompPublishManager *m_pCompPublicationManager;
	//信息状态信息发布器指针
	TopicPublishManager *m_pTopicPublicationManager;
	//数据状态信息发布器指针
	RecordPublishManager *m_pRedordPublicationManager;

	//节点状态信息
	_NODE_INFO* m_pNodeInfo;
	//组件状态信息
	_COMP_INFO* m_pCompInfo;

	//互斥锁
	HANDLE m_hSemNodeInfoMutex;
	HANDLE m_hSemCompInfoMutex;
	HANDLE m_hSemTopicInfoMutex;
	HANDLE m_hSemRecordInfoMutex;


public:
	//记录发送线程
	HANDLE m_hRecordSendTaskId;


	//构造函数,启动监控或记录
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, HANDLE iTaskId, char* pCompName, int iMONITOR, int iRECORD);        //MonitorRecordAgent.h
	//析构函数
	~MonitorRecordAgent (void);	        //MonitorRecordAgent.h
	//初始化函数，启动监控和记录
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);     //MonitorRecordAgent.h
	//初始化函数，启动监控
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);     //MonitorRecordAgent.h


	//初始化函数，启动
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);        //MonitorRecordAgent.h

	//获取DomainParticipant指针
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}             //MonitorRecordAgent.h

	//发送节点状态信息
	_RETURNCODE_T  SendNodeInfo(void);          //MonitorRecordAgent.h
	//发送组件状态信息
	_RETURNCODE_T SendCompInfo(void);           //MonitorRecordAgent.h
	//发送信息流状态信息
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);       //MonitorRecordAgent.h
	//发送数据状态信息
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);         //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();        //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();            //MonitorRecordAgent.h

};

#else

class DDS_DLL MonitorRecordAgent
{
private:
	//DomainParticipant指针
	DomainParticipant *m_pDDSParticipant;
	//本地信息搜集器指针
	LocalDataGather *m_pLocalDataGather;
	//节点状态信息发布管理器指针
	NodePublishManager *m_pNodePublicationManager;
	//组件状态信息发布器指针
	CompPublishManager *m_pCompPublicationManager;
	//信息状态信息发布器指针
	TopicPublishManager *m_pTopicPublicationManager;
	//数据状态信息发布器指针
	RecordPublishManager *m_pRedordPublicationManager;

	//节点状态信息
	_NODE_INFO* m_pNodeInfo;
	//组件状态信息
	_COMP_INFO* m_pCompInfo;

	//互斥锁
	HANDLE m_hSemNodeInfoMutex;
	HANDLE m_hSemCompInfoMutex;
	HANDLE m_hSemTopicInfoMutex;
	HANDLE m_hSemRecordInfoMutex;


public:
	//记录发送线程
	HANDLE m_hRecordSendTaskId;


	//构造函数,启动监控或记录
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, HANDLE iTaskId, char* pCompName, int iMONITOR, int iRECORD);      //MonitorRecordAgent.h
	//析构函数
	~MonitorRecordAgent (void);	
	//初始化函数，启动监控和记录
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);         //MonitorRecordAgent.h
	//初始化函数，启动监控
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);          //MonitorRecordAgent.h


	//初始化函数，启动
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);        //MonitorRecordAgent.h

	//获取DomainParticipant指针
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}              //MonitorRecordAgent.h

	//发送节点状态信息
	_RETURNCODE_T  SendNodeInfo(void);       //MonitorRecordAgent.h
	//发送组件状态信息
	_RETURNCODE_T SendCompInfo(void);       //MonitorRecordAgent.h
	//发送信息流状态信息
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);        //MonitorRecordAgent.h
	//发送数据状态信息
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);        //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();        //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();        //MonitorRecordAgent.h
};
#endif
#endif

#endif

