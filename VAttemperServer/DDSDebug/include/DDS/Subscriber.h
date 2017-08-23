/************************************************************
** 文件名：subscriber.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：subscriber头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _Subscriber_H_
#define _Subscriber_H_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "DDS/DomainEntity.h"

class Participant;
class Discovery;
class TopicDescription;
class DomainEntity;
class DataWriter;
class DataReader;
class DataReaderListener;
class DataWriterListener;

class Subscriber: public DomainEntity
{
private:
    DomainParticipant* m_pRelatedDomainParticipant;
    _DATA_READER_LIST_T m_pDatareaderList; //list <DataReader*>
    unsigned long m_ulMaxDatareader;
    unsigned long m_ulCountDatareader;
    unsigned long m_ulDefaultCacheLength;

	//2013-10-12 hjy 访问m_pDatareaderList互斥锁
#ifdef VXWORKS       //移植
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

public:
    Subscriber(DomainParticipant* pRelatedDomainParticipant,
        unsigned long ulMaxDatareader,
        unsigned long ulDefaultCacheLength);
    virtual ~Subscriber(void);

    DataReader* Create_Datareader (
        TopicDescription* pTopic,
        DataReaderListener* pListener,
        const _DATA_READER_QOS* pQos,
        _STATUS_MASK Mask);
    _RETURNCODE_T Delete_Datareader (DataReader * pDatareader ) ;
    DataReader* Lookup_Datareader (const string strTopicName );

    _RETURNCODE_T DeleteContainedEntities(void);
	_RETURNCODE_T DeleteBuildinEntities(void);//2013-10-14 hjy modify
	
    _RETURNCODE_T Delete_User_Entities(void);

    DomainParticipant* GetRelatedDomainParticipant (void);
    _DATA_READER_LIST_T Find_Datareaders (void);
    _ENTITY_QOS GetDefaultQos (void);

	//2013-10-14 hjy 访问m_DatawriterList互斥锁
#ifdef VXWORKS       //移植
	SEM_ID GetSubMutex()
	{
		return m_hSemMutex;
	}
#else
	HANDLE GetSubMutex()
	{
		return m_hSemMutex;
	}
#endif

	_RETURNCODE_T AddDataReaderToList (DataReader * pDatareader );
};

#endif
