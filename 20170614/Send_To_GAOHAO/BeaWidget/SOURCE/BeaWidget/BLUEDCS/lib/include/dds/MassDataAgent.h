//大数据
/************************************************************
** 文件名：MassDataAgent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<xusen.seu.edu.cn>
** 日  期：2013-07-22
** 修改人：无
** 日  期：无
** 描  述：MassDataAgent头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAAGENT_H_INCLUDED_
#define _DDS_MASSDATAAGENT_H_INCLUDED_

#include "dds/Agent.h"

class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

class MassDataAgent : public Agent
{
public:
    MassDataAgent(DomainParticipant *pDomainParticipant, string strName);
    virtual ~MassDataAgent();

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
