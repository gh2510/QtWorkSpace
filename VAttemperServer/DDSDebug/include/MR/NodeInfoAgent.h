/************************************************************
** �ļ�����NodeInfoAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-24
** ��  ����NodeInfoAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _NodeInfoAGENT_H_
#define _NodeInfoAGENT_H_

#include "dds/Agent.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "NodeInfoDataReader.h"
#include "NodeInfoDataWriter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class NodeInfoAgent : public Agent 
{
public:
	//���캯��
	NodeInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }          //NodeInfoAgent.h
	//��������
	~NodeInfoAgent() {}                //NodeInfoAgent.h

	//����NodeInfoDataWriter
	DataWriter *CreateDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) 
	{
		DataWriter *pNewDataWriter = new NodeInfoDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
		return pNewDataWriter;
	}              //NodeInfoAgent.h

	//����NodeInfoDataReader
	DataReader *CreateDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long ulCacheLength) 
	{
		DataReader *pNewDataReader = new NodeInfoDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
		return pNewDataReader;
	}                       //NodeInfoAgent.h
};

#endif
