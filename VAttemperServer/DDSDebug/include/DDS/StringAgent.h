/************************************************************
** �ļ�����StringAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-04
** �޸��ˣ���
** ��  �ڣ���
** ��  ����StringAgenͷ�ļ�
** ��  ����Version 0.1
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
