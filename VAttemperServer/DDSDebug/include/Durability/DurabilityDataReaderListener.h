/************************************************************
** 文件名：DurabilityDataReaderListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-04-05
** 修改人：无
** 日  期：无
** 描  述：DurabilityDataReaderListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DURABILITYDATAREADERLISTENER_H
#define _DURABILITYDATAREADERLISTENER_H

#include "dds/DataReaderListener.h"
class DataBaseManager;
class DurabilityDataReaderListener : public DataReaderListener
{
private:
	//数据库管理指针
	DataBaseManager *m_pManager;

#ifdef VXWORKS 
	//互斥锁
	SEM_ID m_hSemMutex;
#else
	//互斥锁
	HANDLE m_hSemMutex;
#endif

	char* m_pTopicName;
	char* m_pTypeName;
	//unsigned long m_ipAddress;
//	list<RecordContent> m_recordContentList;
public:
	DurabilityDataReaderListener(DataBaseManager* pManager, char* pTopicName, char* pTypeName);
	~DurabilityDataReaderListener();
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);
};

#endif
