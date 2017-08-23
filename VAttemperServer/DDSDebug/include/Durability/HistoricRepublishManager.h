/************************************************************
** 文件名：HistoricRepublishManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-03-26
** 修改人：无
** 日  期：无
** 描  述：HistoricRepublishManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICREPUBLISHMANAGER_H_INCLUDED_
#define _API_HISTORICREPUBLISHMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
 #include <semLib.h>
#else
#include "Windows.h"
#endif

#pragma warning(disable:4251)

class DomainParticipant;
struct _DISCOVERED_WRITER_DATA;
struct _DISCOVERED_READER_DATA;
class DynamicDataWriter;

struct _DYNAMIC_WRITERRECORD
{
	DynamicDataWriter* pHistoricWriter;
	//DomainParticipant* pDomainParticipant;
	//unsigned long count;
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class HistoricRepublishManager 
{
#else
class DDS_DLL HistoricRepublishManager 
{
#endif
public:
	//获得HistoricRepublishManager单例
    static HistoricRepublishManager* Get_Instance();

	//创建历史数据发布端，开始历史数据发布
	DynamicDataWriter* CreateHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//创建历史数据发布端，开始历史数据发布
	DynamicDataWriter* CreateHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, const char* pTopicName, const char* pTypeName, _ENTITY_QOS* pQos);

	//删除历史数据发布端，停止历史数据发布
	_RETURNCODE_T DeleteHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//创建动态发布主题
	Topic* CreateHistoryDynamicTopic (DomainParticipant* pDomainParticipant, const char* pTopicName, const char* pTypeName);

	//删除动态发布主题
	_RETURNCODE_T DeleteHistoryDynamicTopic (DomainParticipant* pDomainParticipant, char* pTopicName, char* pTypeName);

	//检查发现的订阅信息，对持久性订阅，获取历史数据发布
	_RETURNCODE_T DiscoverNewSubscribe (DomainParticipant* pDomainParticipant, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

	//根据主题、pQos查找对应发布端
	DynamicDataWriter* GetHistoryDynamicDataWriter (unsigned long ulDomainId, const char* pTopicName, const char* pTypeName, _ENTITY_QOS* pQos);

	//发送历史数据
	_RETURNCODE_T SendHistoricData(DomainParticipant* pDomainParticipant, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

private:
	HistoricRepublishManager() {}
	~HistoricRepublishManager() {}

	//单例的指针
    static HistoricRepublishManager *m_pInstance;

	//应用名
	static char* m_pCompName;

	//动态发布端列表
	list<_DYNAMIC_WRITERRECORD> m_HISTORIC_DATADWLIST;

	//互斥锁
#ifdef VXWORKS   //移植
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
