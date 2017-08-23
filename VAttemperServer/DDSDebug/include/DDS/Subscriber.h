/************************************************************
** �ļ�����subscriber.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����subscriberͷ�ļ�
** ��  ����Version 0.1
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

	//2013-10-12 hjy ����m_pDatareaderList������
#ifdef VXWORKS       //��ֲ
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

	//2013-10-14 hjy ����m_DatawriterList������
#ifdef VXWORKS       //��ֲ
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
