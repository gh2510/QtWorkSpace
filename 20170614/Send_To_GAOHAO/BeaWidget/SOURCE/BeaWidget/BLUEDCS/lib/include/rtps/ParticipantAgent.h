/************************************************************
** 文件名：ParticipantAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：ParticipantAgent头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_ParticipantAGENT_H_INCLUDED_
#define _DDS_ParticipantAGENT_H_INCLUDED_

#include "dds/Agent.h"
#include "rtps/ParticipantDataReader.h"
#include "rtps/ParticipantDataWriter.h"

class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class ParticipantAgent : public Agent 
{
public:
    ParticipantAgent(DomainParticipant *pDomainParticipant, string strName)  :
        Agent(pDomainParticipant, strName) { }
    virtual ~ParticipantAgent() {}

    DataWriter *CreateDataWriter(Topic* pTopic,
                                 const _DATA_WRITER_QOS *pQos,
                                 DataWriterListener* pListener,
                                 _STATUS_MASK Mask,
                                 Publisher* pPublisher,
                                 unsigned long ulCacheLength) 
    {
        DataWriter *pNewDataWriter = new ParticipantDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
        return pNewDataWriter;
    }

    DataReader *CreateDataReader(TopicDescription* pTopic,
                                 const _DATA_READER_QOS *pQos,
                                 DataReaderListener* pListener,
                                 _STATUS_MASK Mask,
                                 Subscriber* pSubscriber,
                                 unsigned long ulCacheLength) 
    {
        DataReader *pNewDataReader = new ParticipantDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
        return pNewDataReader;
    }

};

#endif
