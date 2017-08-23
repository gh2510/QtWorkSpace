/************************************************************
** 文件名：RecordPublishManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：RecordPublishManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef RecordPublishManager_hh
#define RecordPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class RecordInfoSendListDataWriter;
class MonitorRecordAgent;

class RecordPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//发送主题信息的DataWriter
	RecordInfoSendListDataWriter *m_pDataWriter;
	//主题
	Topic *m_pTopic;
	//代理的指针
	MonitorRecordAgent *m_pAgent;

	//临时存储个数
	int m_iCounter;

//存储尾部数据线程任务号
#ifdef VXWORKS  
	int m_hTaskId;
#else
	HANDLE m_hTaskId;
#endif

	//数据状态信息临时列表
	_RECORD_INFO m_pRecordInfo[122];

	//互斥锁
#ifdef VXWORKS   
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

public:
	//构造函数
	RecordPublishManager(MonitorRecordAgent *pAgent);             //RecordPublishManager.h
	//析构函数
	~RecordPublishManager();             //RecordPublishManager.h

	//创建RecordInfoSendListDataWriter
	_RETURNCODE_T CreateRecordInfoSendListDW(void);           //RecordPublishManager.h
	//创建主题
	_RETURNCODE_T CreateRecordInfoSendListTopic(void);         //RecordPublishManager.h
	//发送主题信息
	_RETURNCODE_T SendRecordInfo(_RECORD_INFO* pData);           //RecordPublishManager.h

#ifdef VXWORKS
	static _RETURNCODE_T SendRun(RecordPublishManager* pRecordPublishManager);
#else
	static DWORD WINAPI SendRun(RecordPublishManager* pRecordPublishManager);         //RecordPublishManager.h
#endif

	_RETURNCODE_T Send();        //RecordPublishManager.h
	//删除主题
	_RETURNCODE_T DeleteRecordInfoSendListTopic(void);           //RecordPublishManager.h
	//删除RecordInfoSendListDataWriter
	_RETURNCODE_T  DeleteRecordInfoSendListDW(void);           //RecordPublishManager.h

};

#endif
