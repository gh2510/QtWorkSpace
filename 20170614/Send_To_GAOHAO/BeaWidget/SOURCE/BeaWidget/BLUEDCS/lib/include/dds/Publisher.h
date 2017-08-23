/************************************************************
** 文件名：Publisher.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：Publisher头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _Publisher_H_
#define _Publisher_H_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DomainEntity.h"

#ifdef KYLIN
#include <semaphore.h>
#endif

class Participant;
class Discovery;
class Topic;
class DataWriter;
class DomainEntity;	//2013-10-14 hjy modify
class DataReader;
class DataReaderListener;
class DataWriterListener;

class Publisher : public DomainEntity
{
private:
    DomainParticipant* m_pRelatedDomainParticipant;
    _DATA_WRITER_LIST_T m_DatawriterList; //list <DataWrier*>
    unsigned long m_ulMaxDatawriter;
    unsigned long m_ulCountDatawriter;
    unsigned long m_ulDefaultCacheLength;

	//2013-10-12 hjy 访问m_DatawriterList互斥锁
#ifdef VXWORKS       //移植
	SEM_ID m_hSemMutex;
#elif WIN32
	HANDLE m_hSemMutex;
#elif KYLIN
	pthread_mutex_t m_hSemMutex;
#endif

public:
    Publisher(DomainParticipant* pRelatedDomainParticipant, unsigned long ulMaxDatawriter, unsigned long ulDefaultCacheLength);
    virtual ~Publisher(void);

    DataWriter* Create_Datawriter(
        Topic* pTopic,
        DataWriterListener *pListener,
        const _DATA_WRITER_QOS* pQos,
        _STATUS_MASK Mask);
    _RETURNCODE_T Delete_Datawriter(DataWriter * pDatawriter);
    DataWriter* Lookup_Datawriter(const string strTopicName);

    _RETURNCODE_T DeleteContainedEntities(void);
	_RETURNCODE_T DeleteBuildinEntities(void);//2013-10-14 hjy modify

    _RETURNCODE_T Delete_User_Entities(void);

    DomainParticipant* GetRelatedDomainParticipant (void);
    _DATA_WRITER_LIST_T Find_Datawriters(void);
    _ENTITY_QOS GetDefaultQos (void);

	//2013-10-14 hjy 访问m_DatawriterList互斥锁
#ifdef VXWORKS       //移植
	SEM_ID GetPubMutex()
	{
		return m_hSemMutex;
	}
#elif WIN32
	HANDLE GetPubMutex()
	{
		return m_hSemMutex;
	}
#elif KYLIN
	pthread_mutex_t& GetPubMutex()
	{
		return m_hSemMutex;
	}
#endif

	_RETURNCODE_T AddDataWriterToList (DataWriter * pDatawriter );
    //_RETURNCODE_T replaceDatawriter(DataWriter* aDatawriter, DataWriter* bDatawriter);
};

#endif
