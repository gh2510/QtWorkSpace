/************************************************************
** 文件名：DataBaseManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-03-26
** 修改人：无
** 日  期：无
** 描  述：DataBaseManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICDATABASEMANAGER_H_INCLUDED_
#define _API_HISTORICDATABASEMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
 #include <semLib.h>
#else
#include "Windows.h"
#endif

#pragma warning(disable:4251)

struct _HISTORIC_DATA
{
	unsigned long ulDomainId;
	char* pTopic_name;
	char* pType_name; 
	_ENTITY_QOS Qos; 
	unsigned long ulDatalen;
	char* pData; 
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DataBaseManager 
{
#else
class DDS_DLL DataBaseManager 
{
#endif
public:
	//获取DataBaseManager单例指针
    static DataBaseManager* Get_Instance();

	//保存数据
	static _RETURNCODE_T SaveData(_HISTORIC_DATA* pHistoricData);

	//获得数据
	_RETURNCODE_T GetData(unsigned long ulDomainId, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

	//检查是否存在数据
	bool CheckData(unsigned long ulDomainId, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

private:
	DataBaseManager();
	~DataBaseManager();
    static DataBaseManager* m_pInstance;
	static vector<_HISTORIC_DATA*> m_DataList;

#ifdef VXWORKS  
	static _RETURNCODE_T HistoricDataStoreRun(void);
#else
	static DWORD WINAPI HistoricDataStoreRun(void);
#endif

	//互斥锁
#ifdef VXWORKS   //移植
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif

	//历史数据存储尾部数据线程/任务号
#ifdef VXWORKS  
	int m_hTaskId;
#else
	HANDLE m_hTaskId;
#endif

};

#endif
