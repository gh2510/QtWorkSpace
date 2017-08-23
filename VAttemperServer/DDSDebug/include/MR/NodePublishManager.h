/************************************************************
** 文件名：NodePublishManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：NodePublishManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef NodePublishManager_hh
#define  NodePublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class NodeInfoDataWriter;
class MonitorRecordAgent;

class NodePublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//发送主题信息的DataWriter
	NodeInfoDataWriter *m_pDataWriter;
	//主题
	Topic *m_pTopic;
	//代理的指针
	MonitorRecordAgent *m_pAgent;

public:
	//构造函数
	NodePublishManager(MonitorRecordAgent *pAgent);                //NodePublishManager.h
	//析构函数
	~NodePublishManager();                    //NodePublishManager.h

	//创建NodeInfoDataWriter
	_RETURNCODE_T CreateNodeInfoDW(void);                //NodePublishManager.h
	//创建主题
	_RETURNCODE_T CreateNodeInfoTopic(void);              //NodePublishManager.h
	//发送主题信息
	_RETURNCODE_T SendNodeInfo(_NODE_INFO* pData);          //NodePublishManager.h
	//删除主题
	_RETURNCODE_T DeleteNodeInfoTopic(void);            //NodePublishManager.h
	//删除NodeInfoDataWriter
	_RETURNCODE_T  DeleteNodeInfoDW(void);               //NodePublishManager.h

};

#endif
