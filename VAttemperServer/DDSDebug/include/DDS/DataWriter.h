/************************************************************
** �ļ�����DataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAWRITER_H_INCLUDED_
#define _DDS_DATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DomainEntity.h"

class DataWriterListener;
class Writer;
class Publisher;
class Topic;
class HistoryCache;
class DomainEntity;
class Discovery;
class DomainParticipant;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DataWriter : public DomainEntity {
#else
class DDS_DLL DataWriter : public DomainEntity 
{
#endif
protected:
    //�󶨵������ָ��
    Topic* m_pRelatedTopic;

    //pListener������DataWriterͨѶ״̬�仯
    _STATUS_MASK m_Mask;

    //�����ڵķ�����
    Publisher* m_pRelatedPublisher;

    //��������ַ
    HistoryCache* m_pHistoryCache;

    //ָ���ӦWriter��ָ��
    Writer* m_pRelatedWriter;

	//2015-3-17 hjy add MultiNetworkCard support
	bool m_bIsSetNetworkCard;

	int m_iNetworkCardNumber;

    //����ע�����ʵ����ʶInstanceHandle��instance��Ϣ�Ķ�Ӧ��ϵ
    //InstanceMap_DW m_registeredInstance;

    //�ṩ��Deadlineδ�����״̬
    //_OFFERED_DEADLINE_MISSED_STATUS m_OfferedDeadlineMissedStatus;

	//�����ж�ƥ���Ƿ���ɵ��ź���
	HANDLE m_hMatchSemaphore;

public:
    DataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);
    //DataWriter(DataWriter& pDataWriter);
    virtual ~DataWriter();

	//��Ӧ�����
	virtual _RETURNCODE_T AppSet(const char *pAppName)
    {
        return RETURNCODE_OK;
    }

    //���ͱ�DataWriter����Ϣ ���ڷ���
    virtual _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status);

	//2013-09-27 hjy modify ���ڷ���ɾ�����õ�����DataWriter��Ϣ
	virtual _RETURNCODE_T SendDeleteInfo(_ENTITY_STATUS_T Status);

    //ƥ��
    virtual _RETURNCODE_T Match();

    //����DataWriterListener
    virtual _RETURNCODE_T SetListener(DataWriterListener* pListener, _STATUS_MASK Mask);

    //��ȡDataWriterListener
    virtual DataWriterListener* GetListener() 
    {
        return (DataWriterListener*)m_pListener;
    }

    //�������ڵ�DomainParticipant
    DomainParticipant *GetDomainParticipant ();

    //����QoS
    virtual _RETURNCODE_T SetQos(const _DATA_WRITER_QOS* pQos);

    //��ȡQoS
    virtual _DATA_WRITER_QOS* GetQos()
    {
        return (_DATA_WRITER_QOS *)m_pQos;
    }

    //��ȡ��DataWriter�����������
    virtual Topic* GetTopic() 
    {
        return m_pRelatedTopic;
    }

    //��ȡ��DataWriter�����ڵķ�����
    virtual Publisher* GetPublisher() 
    {
        return m_pRelatedPublisher;
    }

    //��ȡ��Ӧ��Writer
    virtual Writer* GetRelatedWriter()
    {
        return m_pRelatedWriter;
    }

    //��ȡ����
    virtual _STATUS_MASK GetMask() 
    {
        return m_Mask;
    }

    //��ȡ��������ַ
    virtual HistoryCache* GetHistoryCache() 
    {
        return m_pHistoryCache;
    }

    //д������Ϻ�֪ͨ����
    virtual _RETURNCODE_T WriteFinished(_SEQUENCE_NUMBER_T SeqNum);

    //��ʱ����
    virtual _RETURNCODE_T DeadlineMissed(const _OFFERED_DEADLINE_MISSED_STATUS& Status);

    _RETURNCODE_T WriteToCache(char* pData,int iSize, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

	//2015-3-17 hjy add MultiNetworkCard support
	bool IsSetNetworkCard()
	{
		return m_bIsSetNetworkCard;
	}

	int GetNetworkCardNumber()
	{
		return m_iNetworkCardNumber;
	}

    _RETURNCODE_T WriteToCache(char* pData,int iSize, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle, _SEQUENCE_NUMBER_T &SeqNum);

	void MatchComplete();
	void WaitForMatch(int iNum);

    DEF_NARROW_METHOD(DataWriter);
};

#endif
