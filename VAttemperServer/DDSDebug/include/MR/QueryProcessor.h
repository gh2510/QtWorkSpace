/************************************************************
** 文件名：QueryProcessor.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：QueryProcessor头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _QueryProcessor_H
#define _QueryProcessor_H

#include "MRBasicTypes.h"
#include "MRReturnCode.h"
#include "RecordQueryRequest.h"
class InfoProcessor;
class RecordQueryRequest;

class QueryProcessor
{
private:
	//处理器指针
	InfoProcessor* m_pProcessor;
	//查询器指针
	static QueryProcessor *m_pQueryProcessor;
	//记录查询指针
	RecordQueryRequest* m_pRecordQueryRequest;

private:
	//构造函数
	QueryProcessor();                 //QueryProcessor.h
	//析构函数
	~QueryProcessor();               //QueryProcessor.h

public:
	//获取监控查询器实例
	static QueryProcessor* GetInstance();           //QueryProcessor.h
	//创建监控查询器实例
	static QueryProcessor* CreateInstance();         //QueryProcessor.h
	static _RETURNCODE_T DeleteInstance();          //QueryProcessor.h

	//实时获取节点固定状态信息
	_RETURNCODE_T GetNodeFixedInfo(unsigned long ulIpAddress,_NODE_FIXED_INFO &nodeInfo);         //QueryProcessor.h
	//实时获取节点实时状态信息
	_RETURNCODE_T GetNodeRealtimeInfo(unsigned long ulIpAddress,_NODE_REALTIME_INFO &nodeInfo);      //QueryProcessor.h
	//实时获取组件状态信息
	_RETURNCODE_T GetComponentInfo(unsigned long ulIpAddress,string strComponentName,_COMP_GINFO &CompInfo);        //QueryProcessor.h
	//获取信息流状态信息
	_RETURNCODE_T GetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicInfo);       //QueryProcessor.h

	_NODE_FIXED_INFO_TX_LIST GetNodeFixedInfoTXList();           //QueryProcessor.h
	_TOPIC_ID_TX_LIST GetTopicIDTXList();         //QueryProcessor.h

	//清空数据库
	_RETURNCODE_T RecordEmpty();          //QueryProcessor.h


};

#endif 
