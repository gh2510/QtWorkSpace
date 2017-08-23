/************************************************************
** �ļ�����DynamicAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-09-10
** ��  ����DynamicAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef __DYNAMICAGENT_H_
#define __DYNAMICAGENT_H_

#include "dds/Agent.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "DynamicDataReader.h"

class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class DynamicAgent : public Agent 
{
public:
	//���캯��
	DynamicAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }   //DynamicAgent.h
	  //��������
	~DynamicAgent() {}   //DynamicAgent.h

	//����DynamicDataWriter
	/*DataWriter *createDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) {
		  DataWriter *newDataWriter = new DynamicDataWriter(pTopic, pQos, pListener, Mask, publisher, ulCacheLength);
		  return newDataWriter;
	}*/

	//����DynamicDataReader
	DataReader *CreateDataReader(TopicDescription* pTopic,
								const _DATA_READER_QOS *pQos,
								DataReaderListener* pListener,
								_STATUS_MASK Mask,
								Subscriber* pSubscriber,
								unsigned long ulCacheLength) 
	{
		DataReader *pNewDataReader = new DynamicDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
		return pNewDataReader;
	}   //DynamicAgent.h
};

#endif
