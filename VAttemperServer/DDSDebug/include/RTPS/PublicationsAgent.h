/************************************************************
** 文件名：PublicationsAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：PublicationsAgent头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_PublicationsAGENT_H_INCLUDED_
#define _DDS_PublicationsAGENT_H_INCLUDED_

#include "dds/Agent.h"
#include "rtps/PublicationsDataReader.h"
#include "rtps/PublicationsDataWriter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class PublicationsAgent : public Agent 
{
public:
    PublicationsAgent(DomainParticipant *pDomainParticipant, string strName) :
        Agent(pDomainParticipant, strName) 
        { 
        }
    virtual ~PublicationsAgent() 
    {
    }

    DataWriter *CreateDataWriter(Topic* pTopic,
                                 const _DATA_WRITER_QOS *pQos,
                                 DataWriterListener* pListener,
                                 _STATUS_MASK Mask,
                                 Publisher* pPublisher,
                                 unsigned long ulCacheLength) 
    {
        DataWriter *pNewDataWriter = new PublicationsDataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength);
        return pNewDataWriter;
    }

    DataReader *CreateDataReader(TopicDescription* pTopic,
                                 const _DATA_READER_QOS *pQos,
                                 DataReaderListener* pListener,
                                 _STATUS_MASK Mask,
                                 Subscriber* pSubscriber,
                                 unsigned long ulCacheLength) 
    {
        DataReader *pNewDataReader = new PublicationsDataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength);
        return pNewDataReader;
    }

};

#endif
