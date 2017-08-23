/************************************************************
** 文件名：TopicInfoAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：TopicInfoAgent头文件
** 版  本：Version 0.1
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
	//构造函数
	TopicInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }   //TopicInfoAgent.h
    //析构函数
	~TopicInfoAgent() {}   //TopicInfoAgent.h

	//创建TopicInfoDataWriter
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

	//创建TopicInfoDataReader
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
