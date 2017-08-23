/************************************************************
** 文件名：Agent.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-03-04
** 修改人：无
** 日  期：无
** 描  述：Agent头文件
** 版  本：Version 0.1
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

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)  || defined(KYLIN)
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

    //创建DataReader
    virtual DataReader *CreateDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength)                               //Agent.h
    {
            return NULL;
    }

	//创建DataWriter
    virtual DataWriter *CreateDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength)                                //Agent.h
    {
            return NULL;
    }

	//获取名称
    string GetName()  //Agent.h
    {
        return m_strName;
    }

private:
    string m_strName;
};

#endif
