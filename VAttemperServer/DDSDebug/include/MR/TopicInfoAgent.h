/************************************************************
** �ļ�����TopicInfoAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����TopicInfoAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _TopicInfoAGENT_H_
#define _TopicInfoAGENT_H_

#include "dds/Agent.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "TopicInfoDataReader.h"
#include "TopicInfoDataWriter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class TopicInfoAgent : public Agent 
{
public:
	//���캯��
	TopicInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }   //TopicInfoAgent.h
    //��������
	~TopicInfoAgent() {}   //TopicInfoAgent.h

	//����TopicInfoDataWriter
	DataWriter *CreateDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) 
	{
		 DataWriter *pNewDataWriter = new TopicInfoDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
		 return pNewDataWriter;
	}   //TopicInfoAgent.h

	//����TopicInfoDataReader
	DataReader *CreateDataReader(TopicDescription* pTopic,
								const _DATA_READER_QOS *pQos,
								DataReaderListener* pListener,
								_STATUS_MASK Mask,
								Subscriber* pSubscriber,
								unsigned long ulCacheLength) 
	{
		  DataReader *pNewDataReader = new TopicInfoDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
		  return pNewDataReader;
	}   //TopicInfoAgent.h
};

#endif
