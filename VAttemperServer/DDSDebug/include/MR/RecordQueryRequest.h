/************************************************************
** 文件名：RecordQueryRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-25
** 修改人：无
** 日  期：无
** 描  述：RecordQueryRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordQueryRequest_H
#define _RecordQueryRequest_H

#include <fstream>
#include <string>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::string;
using namespace std;

#include "MRBasicTypes.h"
#include "MRReturnCode.h"

class RecordQueryRequest
{
public:

#ifdef VXWORKS   
	SEM_ID m_hSemMutexDRSRecord;
	SEM_ID m_hSemMutexRecordContent;
#else
	HANDLE m_hSemMutexDRSRecord;
	HANDLE m_hSemMutexRecordContent;
#endif

	//构造函数
	RecordQueryRequest()
	{	//初始化互斥信号量
#ifdef VXWORKS
		memset(&m_hSemMutexDRSRecord, 0, sizeof(SEM_ID));	
		m_hSemMutexDRSRecord = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
		memset(&m_hSemMutexRecordContent, 0, sizeof(SEM_ID));	
		m_hSemMutexRecordContent = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
#else
		m_hSemMutexDRSRecord = CreateMutex(NULL,FALSE,NULL);
		m_hSemMutexRecordContent = CreateMutex(NULL,FALSE,NULL);
#endif

	}                   //RecordQueryRequest.h
	//析构函数
	~RecordQueryRequest()
	{
#ifdef VXWORKS
		semDelete(m_hSemMutexDRSRecord);
		semDelete(m_hSemMutexRecordContent);
#else
		CloseHandle(m_hSemMutexDRSRecord);
		CloseHandle(m_hSemMutexRecordContent);
#endif

	}                //RecordQueryRequest.h

	//  查询都移植到MFC中

	//清空数据库
	_RETURNCODE_T RecordEmpty();              //RecordQueryRequest.h

};

#endif
