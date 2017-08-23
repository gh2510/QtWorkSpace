/************************************************************
** 文件名：NodeInfoAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-24
** 描  述：NodeInfoAgent头文件
** 版  本：Version 0.1
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
	//构造函数
	NodeInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }          //NodeInfoAgent.h
	//析构函数
	~NodeInfoAgent() {}                //NodeInfoAgent.h

	//创建NodeInfoDataWriter
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

	//创建NodeInfoDataReader
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
