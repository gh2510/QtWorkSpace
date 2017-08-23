/************************************************************
** �ļ�����ParticipantAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ParticipantAgentͷ�ļ�
** ��  ����Version 0.1
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
