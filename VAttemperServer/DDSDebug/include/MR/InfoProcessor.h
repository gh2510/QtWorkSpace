/************************************************************
** 文件名：InfoProcessor.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-22
** 修改人：无
** 日  期：无
** 描  述：InfoProcessor头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _INFOPROCESSOR_H
#define _INFOPROCESSOR_H
#include"MRBasicTypes.h"
#include "MRReturnCode.h"

#include"DDS/DomainParticipant.h"

#ifdef VXWORKS 
#include <semLib.h>
#else
#include "Windows.h" 
#include <io.h>
#endif

#include "TopicInfoDataReader.h"
#include "NodeInfoDataReader.h"
#include "CompInfoDataReader.h"
#include "RecordInfoSendListDataReader.h"
#include "DynamicDataReader.h"
#include "TopicInfoDRListener.h"
#include "NodeInfoDRListener.h"
#include "CompInfoDRListener.h"
#include "RecordInfoSendListDRListener.h"
#include "DynamicDRListener.h"
#include "SubscribeManager.h"

#ifdef VXWORKS
#include "SubscribeManager.h"
#else
class SubscribeManager;
#endif

class DomainParticipant;
class Topic;

class InfoProcessor
{
private:
	//节点全局状态信息存储结构
	_NODE_GINFO_MAP_T m_NodeInfoMap;
	//组件全局状态信息存储结构
	_COMP_GINFO_MAP_T m_CompInfoMap;
	//主题全局状态信息存储结构
	_TOPIC_GLOBAL_INFO_MAP_T m_TopicInfoMap;
	//数据状态信息临时存储结构
	_RECORD_INFO_LIST m_RecordInfoSeq;

	//处理器指针
	static InfoProcessor* m_pProcessor;

#ifdef VXWORKS   
	//组件信息列表的互斥锁
	SEM_ID m_hSemCompWMutex;
	//主题信息列表的互斥锁
	SEM_ID m_hSemTopicWMutex;
	//节点信息列表的互斥锁
	SEM_ID m_hSemNodeWMutex;
	//数据信息文本的互斥锁
	SEM_ID m_hSemRecordInfoWMutex;
#else
	//组件信息列表的互斥锁
	HANDLE m_hSemCompWMutex;
	//主题信息列表的互斥锁
	HANDLE m_hSemTopicWMutex;
	//节点信息列表的互斥锁
	HANDLE m_hSemNodeWMutex;
	//数据信息文本的互斥锁
	HANDLE m_hSemRecordInfoWMutex;
#endif

	//数据记录
	//存储尾部数据线程/任务号
#ifdef VXWORKS  
	int hTaskId;
#else
	HANDLE hTaskId;
#endif
	
public:
	//m_func默认为0；m_func=1，为监控；m_func=2，为记录；m_func=3，为监控记录
	int m_iFunc;

	//记录文本DRSRecord.txt RecordContent.txt序号,初始为1
	//int m_DRSRecordTXTSeq;
	//int m_RecordContentTXTSeq;

	char m_szPathDRSRecordTXTtemp[100];
	char m_szPathRecordContentTXTtemp[100];

	list<_TOPIC_INFO> m_TopicInfoSeq;
	//订阅管理器指针
	SubscribeManager* m_pSubManager;

	_TIME_T m_MaxDiffTime;

	//创建处理器实例
	static InfoProcessor* CreateInstance(void);   //InfoProcessor.h
	//获取处理器实例
	static InfoProcessor* GetInstance(void);   //InfoProcessor.h
	
	static _RETURNCODE_T DeleteInstance(void);   //InfoProcessor.h

	//处理节点状态信息
	_RETURNCODE_T ProcessNodeInfo(_NODE_INFO* pNodeInfo);   //InfoProcessor.h
	//处理组件状态信息
	_RETURNCODE_T ProcessCompInfo(_COMP_INFO* pCompInfo);   //InfoProcessor.h
	//处理主题状态信息
	_RETURNCODE_T ProcessTopicInfo(_TOPIC_INFO* pTopicInfo);   //InfoProcessor.h
	//处理统计信息
	_RETURNCODE_T ProcessRecordInfo(_RECORD_INFO* pRecordInfo);  //InfoProcessor.h


	//处理数据状态信息
	//存储尾部数据线程/任务入口函数
#ifdef VXWORKS
	static _RETURNCODE_T RecordStoreRun();   //InfoProcessor.h
#else
	static DWORD WINAPI RecordStoreRun();    //InfoProcessor.h
#endif

	//获取节点状态信息
	_RETURNCODE_T GetNodeInfo(unsigned long ulIpAddress,
												_NODE_GLOBAL_INFO &NodeGInfo);   //InfoProcessor.h
	//获取组件状态信息
	_RETURNCODE_T GetCompInfo(unsigned long ulIpAddress, 
												string strComponentName,
												_COMP_GINFO& CompInfo);   //InfoProcessor.h
	//获取主题状态信息
	_RETURNCODE_T GetTopicInfo(string strTopicName,
												unsigned long ulDomainId,
												_TOPIC_GLOBAL_INFO& TopicInfo);   //InfoProcessor.h

	_NODE_FIXED_INFO_TX_LIST GetNodeFixedInfoTXList();   //InfoProcessor.h
	_TOPIC_ID_TX_LIST GetTopicIDTXList();    //InfoProcessor.h

	//获取时间
	_TIMESTAMP_T DDSGetCurrentTime(void);   //InfoProcessor.h

	_RETURNCODE_T StartInfoProcessorMonitor(list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	_RETURNCODE_T StartInfoProcessorRecord(list<unsigned long> 	DomainIDList, list<string> TopicName);   //InfoProcessor.h
	_RETURNCODE_T ReleaseInfoProcessorMonitor();   //InfoProcessor.h
	_RETURNCODE_T ReleaseInfoProcessorRecord();   //InfoProcessor.h

	//获取需记录的主题名链表
	_RETURNCODE_T GetRecordTopicNameList(list<string> pTopicName);   //InfoProcessor.h
	//获取文本大小
	//double getTXTsize(char* txtPath);
	//获取当前可记录的文本路径
	//char* getDRSRecordTXTPath();
	//fengjiaqi
	char* GetDBPath();   //InfoProcessor.h
    //fengjiaqi
	char* pPath;    //用于保存数据库路径

private: 
	//构造函数
	InfoProcessor(void)
	{
		m_iFunc = 0;
		//m_DRSRecordTXTSeq = getDRSRecordTxtSeq();
		//m_RecordContentTXTSeq = getRecordContentTxtSeq();
		hTaskId = 0;
		m_pSubManager = NULL;
		m_hSemCompWMutex = NULL;
		m_hSemTopicWMutex = NULL;
		m_hSemNodeWMutex = NULL;
		m_hSemRecordInfoWMutex = NULL;

		m_MaxDiffTime.ulNanosec = 0;
		m_MaxDiffTime.lSecond = 30;
		//fengjiaqi
		pPath = new char[100];
	}   //InfoProcessor.h

	//析构函数
	~InfoProcessor(void)
	{
		if(hTaskId != 0) 
		{

#ifdef VXWORKS 
			taskDelete(hTaskId);
#else
			TerminateThread(hTaskId, 0);
#endif

		}
		hTaskId = 0;
		m_iFunc = 0;
		m_NodeInfoMap.clear();
		m_CompInfoMap.clear();
		m_TopicInfoMap.clear();
		m_RecordInfoSeq.clear();

		if(m_hSemTopicWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemTopicWMutex);
#else
			CloseHandle(m_hSemTopicWMutex);
#endif
		}

		if(m_hSemCompWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemCompWMutex);
#else
			CloseHandle(m_hSemCompWMutex);
#endif
		}

		if(m_hSemNodeWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemNodeWMutex);
#else
			CloseHandle(m_hSemNodeWMutex);
#endif
		}

		if(m_hSemRecordInfoWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemRecordInfoWMutex);
#else
			CloseHandle(m_hSemRecordInfoWMutex);
#endif
		}
		if(m_pSubManager != NULL)
		{
			delete m_pSubManager;
			m_pSubManager = NULL;
		}
		m_pProcessor = NULL;
		//fengjiaqi
		delete[] pPath;
	}    //InfoProcessor.h
	//初始化互斥信号量
	_RETURNCODE_T InitialMonitorSemaphore();   //InfoProcessor.h
	_RETURNCODE_T InitialRecordSemaphore();   //InfoProcessor.h

	//初始化处理器
	static _RETURNCODE_T InitializeMonitor(InfoProcessor* pProcessor, list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	static _RETURNCODE_T InitializeRecord(InfoProcessor* pProcessor, list<unsigned long> 	DomainIDList,list<string> TopicName);  //InfoProcessor.h
	//初始化处理器
	_RETURNCODE_T InitializeMonitor(list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	_RETURNCODE_T InitializeRecord(list<unsigned long> 	DomainIDList, list<string> TopicName);   //InfoProcessor.h

};

#endif
