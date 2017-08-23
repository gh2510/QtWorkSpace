/************************************************************
** 文件名：CompPublishManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-10-05
** 描  述：CompPublishManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/


#ifndef CompsPublishManager_hh
#define CompsPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class CompInfoDataWriter;
class MonitorRecordAgent;

class CompPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;   
	//发送主题信息的DataWriter
	CompInfoDataWriter *m_pDataWriter;   
	//主题
	Topic *m_pTopic;  
	//代理的指针
	MonitorRecordAgent *m_pAgent;   

public:
	//构造函数
	CompPublishManager(MonitorRecordAgent *pAgent);  //CompPublishManager.h
	//析构函数
	~CompPublishManager();  //CompPublishManager.h

	//创建CompInfoDataWriter
	_RETURNCODE_T CreateCompInfoDW(void);  //CompPublishManager.h
	//创建主题
	_RETURNCODE_T CreateCompInfoTopic(void);  //CompPublishManager.h
	//发送主题信息
	_RETURNCODE_T SendCompInfo(_COMP_INFO* pData);  //CompPublishManager.h
	//删除主题
	_RETURNCODE_T DeleteCompInfoTopic(void);  //CompPublishManager.h
	//删除CompInfoDataWriter
	_RETURNCODE_T  DeleteCompInfoDW(void);  //CompPublishManager.h
};

#endif
