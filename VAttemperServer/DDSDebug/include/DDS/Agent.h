/************************************************************
** �ļ�����Agent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-04
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Agentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_AGENT_H_INCLUDED_
#define _DDS_AGENT_H_INCLUDED_

#include "BasicTypes.h"

class DomainParticipant;
class DataReader;
class DataWriter;
class Topic;
class TopicDescription;
class Publisher;
class Subscriber;
class DataReaderListener;
class DataWriterListener;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class Agent
{
#else
class DDS_DLL Agent
{
#endif
public:
    Agent(DomainParticipant *pDomainParticipant, string strName);  //Agent.h
    virtual ~Agent() 
    {
    }

    //����DataReader
    virtual DataReader *CreateDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength)                               //Agent.h
    {
            return NULL;
    }

	//����DataWriter
    virtual DataWriter *CreateDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength)                                //Agent.h
    {
            return NULL;
    }

	//��ȡ����
    string GetName()  //Agent.h
    {
        return m_strName;
    }

private:
    string m_strName;
};

#endif
