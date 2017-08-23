/************************************************************
** �ļ�����DataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-17
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����DataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAREADER_H_INCLUDED_
#define _DDS_DATAREADER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DomainEntity.h"

class DataReaderListener;
class Reader;
class Subscriber;
class TopicDescription;
class HistoryCache;
class Discovery;
class DomainParticipant;
class Participant;

#pragma warning(disable:4251)

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DataReader : public DomainEntity {
#else
class DDS_DLL DataReader : public DomainEntity 
{
#endif
protected:
    //�����ڵĶ�����
    Subscriber* m_pRelatedSubscriber;

    //���ڴ����������˵�TopicDescription��ָ��
    TopicDescription* m_pRelatedTopic;

    //pListener������DataReaderͨѶ״̬�仯
    _STATUS_MASK m_Mask;

    ////��¼ʵ����Ϣ���б�
    //_SAMPLE_INFO_SEQ m_infoSeq;

    //SequenceNumber����
    _SEQ_NUM_TO_HANDLE m_SeqNumtoHandle;

    //��������С
    unsigned long m_ulCacheLength;

    //��������ַ
    HistoryCache* m_pHistoryCache;

    //ָ���ӦReader��ָ��
    Reader* m_pRelatedReader;

	//2015-3-17 hjy add MultiNetworkCard support
	bool m_bIsSetNetworkCard;

	int m_iNetworkCardNumber;

    //������չ���ʵ����ʶInstanceHandle��instance��Ϣ�Ķ�Ӧ��ϵ
    //InstanceMap_DR m_ReceivedInstance;

    //�����Deadlineδ�����״̬
    //_REQUESTED_DEADLINE_MISSED_STATUS m_RequestedDeadlineMissedStatus;

	//�����ж�ƥ���Ƿ���ɵ��ź���
	HANDLE m_hMatchSemaphore;
public:
    DataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);    //DataReader.h
    //DataReader(DataReader& dataReader);
    virtual ~DataReader();

    //��Ӧ�����
    virtual _RETURNCODE_T AppSet(const char *pAppName)      //DataReader.h
    {
        return RETURNCODE_OK;
    }

    //���ͱ�DataReader����Ϣ ���ڷ���
    virtual _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status);//DataReader.h

	//2013-09-27 hjy modify ���ڷ���ɾ�����õ�����DataWriter��Ϣ
	virtual _RETURNCODE_T SendBuildinDataReaderDeleteInfo(_ENTITY_STATUS_T Status);

    //ƥ��
    virtual _RETURNCODE_T Match();  //DataReader.h

    //����QoS
    virtual _RETURNCODE_T SetQos(const _DATA_READER_QOS* pQos);//DataReader.h
    // 
    //��ȡQoS
    virtual _DATA_READER_QOS* GetQos()          //DataReader.h
    {
        return (_DATA_READER_QOS*)m_pQos;
    }

    //�������ڵ�DomainParticipant
    DomainParticipant *GetDomainParticipant (); //DataReader.h

    //���ü�����
    virtual _RETURNCODE_T SetListener(DataReaderListener* pListener, _STATUS_MASK Mask);//DataReader.h

    //��ȡ������
    virtual DataReaderListener* GetListener()   //DataReader.h
    {
        return (DataReaderListener*)m_pListener;
    }

    //��ȡDataReader��ص���������
    virtual TopicDescription* GetTopic()        //DataReader.h
    {
        return m_pRelatedTopic;
    }

    //��������������
    virtual Subscriber* GetSubscriber()         //DataReader.h
    {
        return m_pRelatedSubscriber;
    }

    //��ȡ��Ӧ��Reader
    virtual Reader* GetRelatedReader()          //DataReader.h
    {
        return m_pRelatedReader;
    }

    //��ȡ��������С
    virtual unsigned long GetCacheLength()      //DataReader.h
    {
        return m_ulCacheLength;
    }

    //��ȡ����
    virtual _STATUS_MASK GetMask()              //DataReader.h
    {
        return m_Mask;
    }

    //��ȡ��������ַ
    virtual HistoryCache* GetHistoryCache()     //DataReader.h
    {
        return m_pHistoryCache;
    }

	//2015-3-17 hjy add MultiNetworkCard support
	bool IsSetNetworkCard()
	{
		return m_bIsSetNetworkCard;
	}

	int GetNetworkCardNumber()
	{
		return m_iNetworkCardNumber;
	}

    //���ݵ���֪ͨ
    virtual _RETURNCODE_T DataReceive(_SEQUENCE_NUMBER_T SeqNum, _INSTANCE_HANDLE_T Handle);//DataReader.h

    ////ɾ��ʵ����Ϣ
    //virtual _RETURNCODE_T deleteSampleInfo(_SEQUENCE_NUMBER_T SeqNum);

    //��ʱ����
    virtual _RETURNCODE_T DeadlineMissed(const _REQUESTED_DEADLINE_MISSED_STATUS& Status);  //DataReader.h

    //������
    _RETURNCODE_T ReadCache(char*& pMyDataValue, unsigned long& ulLeng, _INSTANCE_HANDLE_T& Handle, _CHANGE_KIND_T& Kind);//DataReader.h

    _RETURNCODE_T ReadCache(char*& pMyDataValue, unsigned long& ulLeng, _INSTANCE_HANDLE_T& Handle, _CHANGE_KIND_T& Kind, _SEQUENCE_NUMBER_T &Seq);//DataReader.h

    //_RETURNCODE_T readInstanceCache(char*& pMyDataValue, unsigned long& ulLeng, _CHANGE_KIND_T& Kind, _SEQUENCE_NUMBER_T seq);

    _CACHE_CHANGE *GetChange(_SEQUENCE_NUMBER_T SeqNum);    //DataReader.h

    _RETURNCODE_T RemoveChange(_SEQUENCE_NUMBER_T SeqNum);    //DataReader.h

    _RETURNCODE_T GetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind& InstanceState);    //DataReader.h

	void MatchComplete();
	void WaitForMatch(int iNum);

    DEF_NARROW_METHOD(DataReader);
};

#endif
