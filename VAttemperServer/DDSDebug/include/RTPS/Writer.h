/************************************************************
** �ļ�����Writer.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-12
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataWriterͷ�ļ�
** ��  ����Writer 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_WRITER_INCLUDED_H
#define _RTPS_WRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Endpoint.h"

#ifdef VXWORKS
#include <semLib.h>
#else
#include "Windows.h"
#endif

class HistoryCache;
class RequestScheduler;
class DataWriter;

class Writer : public Endpoint
{
public:
    //���캯��
    Writer( _GUID_T            Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList, 
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache      *pHistoryCache, 
        DataWriter        *pDataWriter,
        RequestScheduler  **pScheduleList );

    //��������
    virtual ~Writer();

    //����һ��_CACHE_CHANGE
    _CACHE_CHANGE* NewChange(char *pData, int iLength, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    //��ȡWriter����Ϣ
    //_WRITER_PROXY_DATA* getWriterInfo();
    //virtual HistoryCache* GetWriterCache();
    //virtual _DURATION_T* GetNackResponseDelay();
    //virtual RequestScheduler* GetScheduleList();

    //�����ݷ����������������� �麯�� �ṩ�ӿ�
    virtual _RETURNCODE_T DataSend(_CACHE_CHANGE *pCache) 
    {
        return RETURNCODE_OK;
    };

    virtual _RETURNCODE_T DataSendFindish() 
    {
        return RETURNCODE_OK;
    }

    //���ض�Ӧ�Ļ�����ָ��
    HistoryCache* GetWriterCache() 
    {
        return m_pWriterCache;
    }

    //��ȡ�����±��ĵĽ�ֹ��
    _TIME_T Deadline() 
    {
        //cout<<"get Deadline:"<<m_Deadline.lSecond<<"|"<<m_Deadline.ulNanosec<<endl;
        return m_Deadline;
    }

    //��ȡHeartbeat���ķ�������
    _DURATION_T HeartbeatPeriod() 
    {
        return m_HeartbeatPeriod;
    }

    //���ͽ���
    virtual _RETURNCODE_T DataSendFinish() 
    {
        return RETURNCODE_OK;
    }

    //��ʼ�����ȶ���
    virtual _RETURNCODE_T ScheduleListInit() 
    {
        return RETURNCODE_OK;
    }

    _DURATION_T GetNackResponseDelay() 
    {
        return m_NackResponseDelay;
    };

    _DURATION_T GetNackSuppressionDuration() 
    {
        return m_NackSuppressionDuration;
    };

    virtual _RETURNCODE_T SetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind InstanceState);

	RequestScheduler** Request_Scheduler() 
    {
		return m_pScheduleList;
	}

	DataWriter* GetRelatedDW() 
    {
		return m_pRelatedDataWriter;
	}

	//2014-02-27 hjy modify �������m_HighestSeqNumFinished
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hCacheMutex;
#else
	HANDLE m_hCacheMutex;
#endif

protected:
    //Writer����ģʽ
    bool             m_bPushMode;

    //Heartbeat��������
    _DURATION_T       m_HeartbeatPeriod;

    //�ظ�Nack���ĵ���ʱ
    _DURATION_T       m_NackResponseDelay;

    //����һ��ʱ���ڵ��ظ�Nack����
    _DURATION_T       m_NackSuppressionDuration;

    //��һ�η��ͱ��ĵ�ʱ��
    _TIME_T           m_DataSendTime;

    //�����±��ĵĽ�ֹ��
    _DURATION_T       m_Deadline;

    //��һ�����ɵ�Change�����к�
    _SEQUENCE_NUMBER_T m_LastChangeSequence;

    //�Ѿ��ɹ����͵�Change�����к�
    _SEQUENCE_NUMBER_T m_HighestSeqNumFinished;

    //��Ӧ��DDS DataWriter
    DataWriter       *m_pRelatedDataWriter;

    //��Ӧ�Ļ�����
    HistoryCache     *m_pWriterCache;

    //���ȶ��У�0ΪImmeditRequestScheduler��1ΪPeriodRequestScheduler
    RequestScheduler **m_pScheduleList;

    //������ �������m_DataSendTime
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemTimeMutex;
#else
	HANDLE m_hSemTimeMutex;
#endif

    //���淢�͹���ʵ����ʶInstanceHandle��instance��Ϣ�Ķ�Ӧ��ϵ
    _INSTANCE_MAP_W m_SentInstance;

    //�ṩ��Deadlineδ�����״̬
    _OFFERED_DEADLINE_MISSED_STATUS m_OfferedDeadlineMissedStatus;

	//pQosָ��
	//2013-10-12 hjy modify
	_DATA_WRITER_QOS* m_pQos;
};

#endif
