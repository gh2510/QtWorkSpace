/************************************************************
** 文件名：HistoricGatherManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-03-26
** 修改人：无
** 日  期：无
** 描  述：HistoricGatherManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICGATHERMANAGER_H_INCLUDED_
#define _API_HISTORICGATHERMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
 #include <semLib.h>
#else
#include "Windows.h"
#endif

class DomainParticipant;
struct _DISCOVERED_WRITER_DATA;
class DynamicDataReader;
class HistoricRepublishManager;
class DataBaseManager;

#pragma warning(disable:4251)

struct _DYNAMIC_READER_RECORD
{
	DynamicDataReader* pHistoricReader;
	DomainParticipant* pDomainParticipant;
	unsigned long ulCount;
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class HistoricGatherManager 
{
#else
class DDS_DLL HistoricGatherManager 
{
#endif
public:
	//获得HistoricGatherManager单例
    static HistoricGatherManager* Get_Instance();

	//创建HistoricGatherManager单例
    static HistoricGatherManager* Create_Instance(list<unsigned long> DomainIDList);

	//检查发现的发布信息，对持久性发布创建对应订阅端、历史数据重发布端
    _RETURNCODE_T DiscoverNewPublish (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//发现订阅删除信息，删除对应订阅端
	_RETURNCODE_T DiscoverPublishDeletion (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//创建历史数据订阅端，开始历史数据接收
	DynamicDataReader* CreateHistoryDynamicDataReader (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//删除历史数据订阅端，停止历史数据接收
	_RETURNCODE_T DeleteHistoryDynamicDataReader (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//创建动态订阅主题
	Topic* CreateHistoryDynamicTopic (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//删除动态订阅主题
	_RETURNCODE_T DeleteHistoryDynamicTopic (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//获得历史数据重发布者
	HistoricRepublishManager* GetHistoricRepublishManager()
    {
		return m_pRepublishManager;
	}

private:
	HistoricGatherManager();

	~HistoricGatherManager();

	//HistoricGatherManager单例的指针
    static HistoricGatherManager *m_pInstance;

	//DomainParticipant 指针列表
    static list<DomainParticipant*> m_pDomainParticipantList;

	//动态订阅端列表
	list<_DYNAMIC_READER_RECORD> m_HistoricDataDRList;

	//历史数据存储管理的指针
	DataBaseManager* m_pDataBaseManager;

	//历史数据重发布管理者的指针
	HistoricRepublishManager* m_pRepublishManager;

	//应用名
	static char* m_pCompName;

	//互斥锁
#ifdef VXWORKS   //移植
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
