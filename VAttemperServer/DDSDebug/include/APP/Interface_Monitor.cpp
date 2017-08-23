/************************************************************
** �ļ�����Interface_Monitor.cpp
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�ͿӨ
** ��  �ڣ�2011-03-05
** ��  ���������ṩ��ط���ӿ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#include "Interface_Monitor.h"
#include "DDS/CReadConfig.h"

#pragma warning(disable:4996)
/************************************************************
** ��������ServStartMonitorServer
** ��  �룺��
** ��  ������
** ����������������ط���
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
void ServStartMonitorServer()
{
	InfoProcessor *pProcessor = InfoProcessor::GetInstance();
	if (pProcessor == NULL)		
        pProcessor = InfoProcessor::CreateInstance();

	//�������ļ�����ȡ��ص���ID�����м�ء�
	//����ص����ڿ�����ʱ��ͱ���ȷ�������治�ٸ��ġ�
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

	ulDomainIDList.sort();	//�������ȥ���ظ�ֵ
	ulDomainIDList.unique();	//ȥ���ظ�ֵ

	pProcessor->StartInfoProcessorMonitor(ulDomainIDList);
	cout<<"StartInfoProcessorMonitor sucessfull..."<<endl;

}


/************************************************************
** ��������ServGetNodeFixedInfo
** ��  �룺pIpAddress
**         pIpAddress--�ڵ�ip
** ��  ����NodeFixedInfo--���ڷ��ز�ѯ���
** �����������ڵ�̶���Ϣʵʱ��ѯ
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
_RETURNCODE_T ServGetNodeFixedInfo(char* pIpAddress,_NODE_FIXED_INFO &NodeFixedInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetNodeFixedInfo(IpCharToInt(pIpAddress),NodeFixedInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** ��������ServGetNodeRealtimeInfo
** ��  �룺pIpAddress
**         pIpAddress--�ڵ�ip
** ��  ����NodeRealTimeInfo--������������ڷ��ز�ѯ���
** �����������ڵ�ʵʱ��Ϣʵʱ��ѯ
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
_RETURNCODE_T ServGetNodeRealtimeInfo(char* pIpAddress,_NODE_REALTIME_INFO &NodeRealTimeInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetNodeRealtimeInfo(IpCharToInt(pIpAddress), NodeRealTimeInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** ��������ServGetComponentInfo
** ��  �룺pIpAddress,strComponentName
**         pIpAddress--�ڵ�ip
**         strComponentName--�����
** ��  ����CompGInfo--������������ڷ��ز�ѯ���
** ������������ȡӦ�����״̬��Ϣ
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
_RETURNCODE_T ServGetComponentInfo(char* pIpAddress,string strComponentName,_COMP_GINFO &CompGInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetComponentInfo(IpCharToInt(pIpAddress), strComponentName, CompGInfo);
	return RETURNCODE_ERROR;
}


/************************************************************
** ��������ServGetDataStreamInfo
** ��  �룺strTopicName,ulDomainId
**         strTopicName--������
**         ulDomainId--������������id
** ��  ����TopicGlobalInfo--������������ڷ��ز�ѯ���
** ���������������Ϣ����Ϣ
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
_RETURNCODE_T ServGetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicGlobalInfo)
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->GetDataStreamInfo(strTopicName,ulDomainId, TopicGlobalInfo);
	return RETURNCODE_ERROR;
}

/************************************************************
** ��������ServGetNodeFixedInfoTXList
** ��  �룺��
** ��  ����NodeFixedInfoSeq--������������ڷ��ز�ѯ���
** ������������ȡ�ڵ�̶���Ϣ�б�
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
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
** ��������ServGetTopicIDTXList
** ��  �룺��
** ��  ����TopicIDSeq--������������ڷ��ز�ѯ���
** ������������ȡ������Ϣ�б�
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
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



