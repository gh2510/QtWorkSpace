/************************************************************
** �ļ�����Reader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Readerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_READER_H_INCLUDED_
#define _RTPS_READER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Endpoint.h"

//����
class DataReader;
class HistoryCache;
class RequestScheduler;

class Reader : public Endpoint 
{
public:
    //���캯��
    Reader (_GUID_T Guid,
        const _DATA_READER_QOS* pQos,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        RequestScheduler** pRequestScheduler,
        HistoryCache *pHistoryCache,
        DataReader *pDataReader);

    //��������
    ~Reader ();

    //����_CACHE_CHANGE
    _CACHE_CHANGE *NewChange(_GUID_T WriterGuid, char *pMessage, unsigned long ulLength, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);
    _CACHE_CHANGE *NewChange(_GUID_T WriterGuid, char *pMessage, unsigned long ulLength, _SEQUENCE_NUMBER_T SeqNum, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    //֪ͨDDS DataReader���ݵ���
    _RETURNCODE_T DataNotify(_SEQUENCE_NUMBER_T LocalSeqNum);

    //��ȡ�����ظ�Heartbeat���ĵ�ʱ��
    _DURATION_T HeartbeatSuppressionDuration() 
    {
        return m_HeartbeatSuppressionDuration;
    }

    //��ȡHeartbeat���Ļظ���ʱ
    _DURATION_T HearbeatResponseDelay() 
    {
        return m_HeartbeatResponseDelay;
    }

    //��ȡ���ձ��ĵĽ�ֹ��Deadline
    _DURATION_T Deadline() {
        return m_Deadline;
    }

    //��ʼ�����ȶ���
    virtual _RETURNCODE_T ScheduleListInit() 
    {
        return RETURNCODE_OK;
    }

    //����Ƿ�����Ӧ��Writer�ڷ��͸�ʵ��
    //bool noWriters(_INSTANCE_HANDLE_T Handle);

    //��ȡʵ��״̬
    _RETURNCODE_T GetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind& InstanceState);

	//����ʵ��״̬
	_RETURNCODE_T InstanceUpdate(_GUID_T WriterGuid, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    _SEQUENCE_NUMBER_T GetNewChangeSeqNum() 
    {
        return ++m_LastChangeSeqNum;
    }

    void SetSeqNumNotify(_SEQUENCE_NUMBER_T SeqNum) 
    {
        m_HighestSeqNumNotify = SeqNum;
    }

protected:
    //Heartbeat���Ļظ���ʱ
    _DURATION_T m_HeartbeatResponseDelay;

    //�����ظ���Heartbeat���ĵ�ʱ��
    _DURATION_T m_HeartbeatSuppressionDuration;

    //�����±��ĵĽ�ֹ��
    _DURATION_T m_Deadline;

    //�������ɵ�Change�����к�
    _SEQUENCE_NUMBER_T m_LastChangeSeqNum;

    //���ȶ��У�0ΪImmeditRequestScheduler��1ΪPeriodRequestScheduler
    RequestScheduler** m_pScheduleList;

    //��Ӧ��DDS DataReader
    DataReader *m_pRelatedDataReader;

    //��Ӧ�Ļ�����
    HistoryCache *m_pReaderCache;

    //������չ���ʵ����ʶInstanceHandle��instance��Ϣ�Ķ�Ӧ��ϵ
    _INSTANCE_MAP_R m_ReceivedInstance;

    //������ �������m_ReceivedInstance
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemRecvInstMutex;
#else
	HANDLE m_hSemRecvInstMutex;
#endif

    //�����Deadlineδ�����״̬
    _REQUESTED_DEADLINE_MISSED_STATUS m_RequestedDeadlineMissedStatus;

    //�Ͻ���SequenceNumber
    _SEQUENCE_NUMBER_T m_HighestSeqNumNotify;

	//pQosָ��
	//2013-10-12 hjy modify
	_DATA_READER_QOS* m_pQos;
};

#endif
