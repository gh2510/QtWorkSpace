/************************************************************
** 文件名：DynamicAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-09-10
** 描  述：DynamicAgent头文件
** 版  本：Version 0.1
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
	//构造函数
	DynamicAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }   //DynamicAgent.h
	  //析构函数
	~DynamicAgent() {}   //DynamicAgent.h

	//创建DynamicDataWriter
	/*DataWriter *createDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) {
		  DataWriter *newDataWriter = new DynamicDataWriter(pTopic, pQos, pListener, Mask, publisher, ulCacheLength);
		  return newDataWriter;
	}*/

	//创建DynamicDataReader
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
