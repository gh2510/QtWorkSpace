/************************************************************
** �ļ�����QueryProcessor.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����QueryProcessorͷ�ļ�
** ��  ����Version 0.1
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
	//������ָ��
	InfoProcessor* m_pProcessor;
	//��ѯ��ָ��
	static QueryProcessor *m_pQueryProcessor;
	//��¼��ѯָ��
	RecordQueryRequest* m_pRecordQueryRequest;

private:
	//���캯��
	QueryProcessor();                 //QueryProcessor.h
	//��������
	~QueryProcessor();               //QueryProcessor.h

public:
	//��ȡ��ز�ѯ��ʵ��
	static QueryProcessor* GetInstance();           //QueryProcessor.h
	//������ز�ѯ��ʵ��
	static QueryProcessor* CreateInstance();         //QueryProcessor.h
	static _RETURNCODE_T DeleteInstance();          //QueryProcessor.h

	//ʵʱ��ȡ�ڵ�̶�״̬��Ϣ
	_RETURNCODE_T GetNodeFixedInfo(unsigned long ulIpAddress,_NODE_FIXED_INFO &nodeInfo);         //QueryProcessor.h
	//ʵʱ��ȡ�ڵ�ʵʱ״̬��Ϣ
	_RETURNCODE_T GetNodeRealtimeInfo(unsigned long ulIpAddress,_NODE_REALTIME_INFO &nodeInfo);      //QueryProcessor.h
	//ʵʱ��ȡ���״̬��Ϣ
	_RETURNCODE_T GetComponentInfo(unsigned long ulIpAddress,string strComponentName,_COMP_GINFO &CompInfo);        //QueryProcessor.h
	//��ȡ��Ϣ��״̬��Ϣ
	_RETURNCODE_T GetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicInfo);       //QueryProcessor.h

	_NODE_FIXED_INFO_TX_LIST GetNodeFixedInfoTXList();           //QueryProcessor.h
	_TOPIC_ID_TX_LIST GetTopicIDTXList();         //QueryProcessor.h

	//������ݿ�
	_RETURNCODE_T RecordEmpty();          //QueryProcessor.h


};

#endif 
