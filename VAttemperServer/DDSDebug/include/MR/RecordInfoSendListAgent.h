/************************************************************
** �ļ�����RecordInfoSendListAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����RecordInfoSendListAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordInfoSendListAGENT_H_
#define _RecordInfoSendListAGENT_H_

#include "dds/Agent.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "RecordInfoSendListDataReader.h"
#include "RecordInfoSendListDataWriter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class RecordInfoSendListAgent : public Agent 
{
public:
	//���캯��
	RecordInfoSendListAgent(DomainParticipant *pDomainParticipant, string strName)  :	 Agent(pDomainParticipant, strName) { }          //RecordInfoSendListAgent.h
	//��������
	~RecordInfoSendListAgent() {}             //RecordInfoSendListAgent.h

	//����RecordInfoSendListDataWriter
	DataWriter *CreateDataWriter(Topic* pTopic,
								const _DATA_WRITER_QOS *pQos,
								DataWriterListener* pListener,
								_STATUS_MASK Mask,
								Publisher* pPublisher,
								unsigned long ulCacheLength) 
	{
		DataWriter *pNewDataWriter = new RecordInfoSendListDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
		return pNewDataWriter;
	}                  //RecordInfoSendListAgent.h

	//����RecordInfoSendListDataReader
	DataReader *CreateDataReader(TopicDescription* pTopic,
								const _DATA_READER_QOS *pQos,
								DataReaderListener* pListener,
								_STATUS_MASK Mask,
								Subscriber* pSubscriber,
								unsigned long ulCacheLength) 
	{
		DataReader *pNewDataReader = new RecordInfoSendListDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
		return pNewDataReader;
	}                //RecordInfoSendListAgent.h
};

#endif
