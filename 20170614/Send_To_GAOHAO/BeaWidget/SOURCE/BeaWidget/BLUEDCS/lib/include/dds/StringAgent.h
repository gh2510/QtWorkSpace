/************************************************************
** 文件名：StringAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-03-04
** 修改人：无
** 日  期：无
** 描  述：StringAgen头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_STRINGAGENT_H_INCLUDED_
#define _DDS_STRINGAGENT_H_INCLUDED_

#include "dds/Agent.h"

class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class StringAgent : public Agent
{
public:
    StringAgent(DomainParticipant *pDomainParticipant, string strName);
    virtual ~StringAgent();

    DataWriter *CreateDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    DataReader *CreateDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);
};

#endif
