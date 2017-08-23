/************************************************************
** �ļ�����CompInfoAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/04/26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/8/24
** ��  ����CompInfoAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef __CompInfoAGENT_H_
#define __CompInfoAGENT_H_

#include "dds/Agent.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "CompInfoDataReader.h"
#include "CompInfoDataWriter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class CompInfoAgent : public Agent 
{
public:
	//���캯��
	CompInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }    //CompInfoAgent.h
	//��������
	~CompInfoAgent() {}           //CompInfoAgent.h

	//����CompInfoDataWriter
	DataWriter *CreateDataWriter(Topic* pTopic,
								const _DATA_WRITER_QOS *pQos,
								DataWriterListener* pListener,
								_STATUS_MASK Mask,
								Publisher* pPublisher,
								unsigned long ulCacheLength) 
	 {
		DataWriter *pNewDataWriter = new CompInfoDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
		return pNewDataWriter;
	 }         //CompInfoAgent.h                                               

	  //����CompInfoDataReader
	 DataReader *CreateDataReader(TopicDescription* pTopic,
								const _DATA_READER_QOS *pQos,
								DataReaderListener* pListener,
								_STATUS_MASK Mask,
								Subscriber* pSubscriber,
								unsigned long ulCacheLength) 
	 {
		DataReader *pNewDataReader = new CompInfoDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
		return pNewDataReader;
	 }   //CompInfoAgent.h
};

#endif
