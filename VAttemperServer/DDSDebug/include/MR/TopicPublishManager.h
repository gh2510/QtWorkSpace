/************************************************************
** 文件名：TopicPublishManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：TopicPublishManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef TopicPublishManager_hh
#define TopicPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class TopicInfoDataWriter;
class MonitorRecordAgent;

class TopicPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//发送主题信息的DataWriter
	TopicInfoDataWriter *m_pDataWriter;
	//主题
	Topic *m_pTopic;
	//代理的指针
	MonitorRecordAgent *m_pAgent;

public:
	//构造函数
	TopicPublishManager(MonitorRecordAgent *pAgent);   //TopicPublishManager.h
	//析构函数
	~TopicPublishManager();  //TopicPublishManager.h

	//创建TopicInfoDataWriter
	_RETURNCODE_T CreateTopicInfoDW(void);  //TopicPublishManager.h
	//创建主题
	_RETURNCODE_T CreateTopicInfoTopic(void);  //TopicPublishManager.h
	//发送主题信息
	_RETURNCODE_T SendTopicInfo(_TOPIC_INFO* pData);  //TopicPublishManager.h
	//删除主题
	_RETURNCODE_T DeleteTopicInfoTopic(void);  //TopicPublishManager.h
	//删除TopicInfoDataWriter
	_RETURNCODE_T  DeleteTopicInfoDW(void);  //TopicPublishManager.h

};

#endif
