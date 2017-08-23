/************************************************************
** 文件名：CompInfoAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011/04/26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011/8/24
** 描  述：CompInfoAgent头文件
** 版  本：Version 0.1
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
	//构造函数
	CompInfoAgent(DomainParticipant *pDomainParticipant, string strName)  :	  Agent(pDomainParticipant, strName) { }    //CompInfoAgent.h
	//析构函数
	~CompInfoAgent() {}           //CompInfoAgent.h

	//创建CompInfoDataWriter
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

	  //创建CompInfoDataReader
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
