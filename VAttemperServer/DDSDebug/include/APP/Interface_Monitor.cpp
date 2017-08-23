/************************************************************
** 文件名：Interface_Monitor.cpp
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：涂莹
** 日  期：2011-03-05
** 描  述：向外提供监控服务接口
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#include "Interface_Monitor.h"
#include "DDS/CReadConfig.h"

#pragma warning(disable:4996)
/************************************************************
** 函数名：ServStartMonitorServer
** 输  入：无
** 输  出：无
** 功能描述：开启监控服务
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
void ServStartMonitorServer()
{
	InfoProcessor *pProcessor = InfoProcessor::GetInstance();
	if (pProcessor == NULL)		
        pProcessor = InfoProcessor::CreateInstance();

	//读配置文件，获取监控的域ID，进行监控。
	//被监控的域在开启的时候就必须确定，后面不再更改。
	list<unsigned long> 	ulDomainIDList;
	_RETURNCODE_T Ret;
	int iMonitorDomainCount;
	int iDomainId;	
	
#ifdef VXWORKS
	char* pPath = "/ata0a/DDS/ddsconfig.conf";
#else
	char* pPath = "./common/ddsconfig.conf";
#endif

	CReadConfig* pConfigReader = new CReadConfig;

	Ret = pConfigReader->GetConfigInt("MonitorDomainCount", "MonitorDomainCount", &iMonitorDomainCount, pPath);
	if (Ret != RETURNCODE_OK || iMonitorDomainCount <= 0) 
    {
		return;
	}
	for(int I = 0; I < iMonitorDomainCount; I ++)
    {
		char szDomainIdtemp[50];
		sprintf( szDomainIdtemp, "MonitorDomain[%d]", I);
		Ret = pConfigReader->GetConfigInt("MonitorDomainCount", szDomainIdtemp, &iDomainId, pPath);
		if (Ret != RETURNCODE_OK) 
        {
			return;
		}
		ulDomainIDList.push_back((unsigned long)iDomainId);
	}

	ulDomainIDList.sort();	//排序才能去除重复值
	ulDomainIDList.unique();	//去除重复值

	pProcessor->StartInfoProcessorMonitor(ulDomainIDList);
	cout<<"StartInfoProcessorMonitor sucessfull..."<<endl;

}


/************************************************************
** 函数名：ServGetNodeFixedInfo
** 输  入：pIpAddress
**         pIpAddress--节点ip
** 输  出：NodeFixedInfo--用于返回查询结果
** 功能描述：节点固定信息实时查询
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_RETURNCODE_T ServGetNodeFixedInfo(char* pIpAddress,_NODE_FIXED_INFO &NodeFixedInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetNodeFixedInfo(IpCharToInt(pIpAddress),NodeFixedInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** 函数名：ServGetNodeRealtimeInfo
** 输  入：pIpAddress
**         pIpAddress--节点ip
** 输  出：NodeRealTimeInfo--输出参数，用于返回查询结果
** 功能描述：节点实时信息实时查询
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_RETURNCODE_T ServGetNodeRealtimeInfo(char* pIpAddress,_NODE_REALTIME_INFO &NodeRealTimeInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetNodeRealtimeInfo(IpCharToInt(pIpAddress), NodeRealTimeInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** 函数名：ServGetComponentInfo
** 输  入：pIpAddress,strComponentName
**         pIpAddress--节点ip
**         strComponentName--组件名
** 输  出：CompGInfo--输出参数，用于返回查询结果
** 功能描述：获取应用组件状态信息
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_RETURNCODE_T ServGetComponentInfo(char* pIpAddress,string strComponentName,_COMP_GINFO &CompGInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetComponentInfo(IpCharToInt(pIpAddress), strComponentName, CompGInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** 函数名：ServGetDataStreamInfo
** 输  入：strTopicName,ulDomainId
**         strTopicName--主题名
**         ulDomainId--主题所属的域id
** 输  出：TopicGlobalInfo--输出参数，用于返回查询结果
** 功能描述：获得信息流信息
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_RETURNCODE_T ServGetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicGlobalInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetDataStreamInfo(strTopicName,ulDomainId, TopicGlobalInfo);
	return RETURNCODE_ERROR;
}

/************************************************************
** 函数名：ServGetNodeFixedInfoTXList
** 输  入：无
** 输  出：NodeFixedInfoSeq--输出参数，用于返回查询结果
** 功能描述：获取节点固定信息列表
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_NODE_FIXED_INFO_SEQ ServGetNodeFixedInfoTXList()
{
	_NODE_FIXED_INFO_TX_LIST::iterator iterNode;
	_NODE_FIXED_INFO_SEQ NodeFixedInfoSeq;
	NodeFixedInfoSeq.iCount = 0;
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if (pQuery != NULL)
	{
		_NODE_FIXED_INFO_TX_LIST Node = pQuery->GetNodeFixedInfoTXList();
		for(iterNode = Node.begin(); iterNode != Node.end(); iterNode++ )
		{
			strcpy(NodeFixedInfoSeq.m_nodeFixedInfoTXSeq[NodeFixedInfoSeq.iCount].szHostName, (*iterNode).szHostName);
			NodeFixedInfoSeq.m_nodeFixedInfoTXSeq[NodeFixedInfoSeq.iCount].ulIpAddress = (*iterNode).ulIpAddress;
			NodeFixedInfoSeq.m_nodeFixedInfoTXSeq[NodeFixedInfoSeq.iCount].bValid = (*iterNode).bValid;
			NodeFixedInfoSeq.iCount ++;
		}

/*		cout<<"NodeFixedInfoSeq.iCount: "<<NodeFixedInfoSeq.iCount<<endl;*/
	}
	return NodeFixedInfoSeq;
}


/************************************************************
** 函数名：ServGetTopicIDTXList
** 输  入：无
** 输  出：TopicIDSeq--输出参数，用于返回查询结果
** 功能描述：获取主题信息列表
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_TOPIC_ID_SEQ ServGetTopicIDTXList()
{
	_TOPIC_ID_TX_LIST::iterator iterTopic;
	_TOPIC_ID_SEQ TopicIDSeq;
	TopicIDSeq.iCount = 0;
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
	{
		_TOPIC_ID_TX_LIST Topic = pQuery->GetTopicIDTXList();
		for(iterTopic = Topic.begin(); iterTopic != Topic.end(); iterTopic++)
		{
			strcpy(TopicIDSeq.pTopicIDTXSeq[TopicIDSeq.iCount].szName,(*iterTopic).szName);
			TopicIDSeq.pTopicIDTXSeq[TopicIDSeq.iCount].ulDomainId = (*iterTopic).ulDomainId;
			TopicIDSeq.pTopicIDTXSeq[TopicIDSeq.iCount].bValid = (*iterTopic).bValid;
			TopicIDSeq.iCount ++;
		}
/*		cout<<"TopicIDSeq.iCount: "<<TopicIDSeq.iCount<<endl;*/
	}
	return TopicIDSeq;
}



