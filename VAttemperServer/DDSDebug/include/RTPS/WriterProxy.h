/************************************************************
** �ļ�����WriterProxy.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����WriterProxyͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_WRITERPROXY_H_INCLUDED_
#define _RTPS_WRITERPROXY_H_INCLUDED_

#include "BasicTypes.h"

#ifdef VXWORKS
#include <semLib.h>
#else
#include "Windows.h"
#endif

class StatefulReader;

class WriterProxy 
{
public:
    //���캯��
    WriterProxy(_GUID_T AWriterGuid,
        StatefulReader *pReader,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList);

    //��������
    virtual ~WriterProxy();

private:
    //ά���ӷ����˽��յ����ݵ�״̬��Ϣ
    _RETURNCODE_T ChangeFromWriterAdd(_CHANGE_FROM_WRITER *pChangeFromWriter);
    _RETURNCODE_T ChangeFromWriterRemove(_SEQUENCE_NUMBER_T RemoteSeqNum);

public:
    //��ȡ�����˵�GUID
    _GUID_T WriterGuid() 
    {
        return m_RemoteWriterGuid;
    }

    //��ȡ��һ���ύ���ݵ�ʱ��
    _TIME_T DataNotifyTime() 
    {
        //�ӻ�����
#ifdef VXWORKS   //��ֲ
	    semTake(m_hSemMutex, WAIT_FOREVER);
#else
    	WaitForSingleObject(m_hSemMutex,INFINITE);
#endif

        _TIME_T Temp = m_DataNotifyTime;

        //�⻥����
#ifdef VXWORKS   //��ֲ
		semGive(m_hSemMutex);
#else
		ReleaseMutex(m_hSemMutex);
#endif
        return Temp;
    }

    //��ȡԤ����һ�η���AckNack���ĵ�ʱ��
    _TIME_T NextAckNackTime() 
    {
        return m_NextAckNackTime;
    }

    //������һ�η���AckNack���ĵ�ʱ��
    _RETURNCODE_T NextAckNackTimeSet (_TIME_T Time) 
    {
        m_NextAckNackTime = Time;
        return RETURNCODE_OK;
    }

    //��ȡ������ַ
    _LOCATOR_T UnicastLocatorGet() 
    {
        if (m_UnicastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_UnicastLocatorList[0];
    }

    //��ȡ�ಥ��ַ
    _LOCATOR_T MulticastLocatorGet() 
    {
        if (m_MulticastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_MulticastLocatorList[0];
    }

    //��ȡ�Ѿ��ɹ������������кţ���������DDS DataReader�ύ���������к�
    _SEQUENCE_NUMBER_T HaveAvailableChange();

    //���Է��͹�����ظ�Heartbeat����
    bool HeartbeatIgnore(_COUNT_T HeartbeatCount);

    //��ѯ�Ƿ�������ȱʧ
    bool MissingChanges();

    //�������ݽ���״̬
    _RETURNCODE_T ReceivedChangeSet(
        _SEQUENCE_NUMBER_T RemoteSeqNum,
        _SEQUENCE_NUMBER_T LocalSeqNum);

    //���±��Ķ�ʧ״̬
    _RETURNCODE_T LostChangesUpdate(_SEQUENCE_NUMBER_T FirstAvailableSeqNum);

    //���±���ȱʧ״̬
    _RETURNCODE_T MissingChangesUpdate(
        _SEQUENCE_NUMBER_T FirstAvailableSeqNum,
        _SEQUENCE_NUMBER_T LastAvailableSeqNum);

    //���±��ĵ��ύ״̬
    _RETURNCODE_T NotifyChangesUpdate(_SEQUENCE_NUMBER_T RemoteSeqNum);


    //��ȡAckNack����
    _RETURNCODE_T AckNackMessageGet(char **pMessage, unsigned long *pLength);

	//��ȡm_HighestSeqNumAvailable
	_SEQUENCE_NUMBER_T GetHighestSeqNumAvailable()
    {
		return m_HighestSeqNumAvailable;
	}

    //���ChangeFromWriterList�Ƿ����RemoteSeqNum�ļ�¼
    _SEQUENCE_NUMBER_T ExistChange(_SEQUENCE_NUMBER_T RemoteSeqNum);

	//2013-11-04 hjy modify
	StatefulReader * GetRelatedRTPSReader()
	{
		return m_pRelatedReader;
	}

private:
    //Զ�˷����˵�GUID
    _GUID_T m_RemoteWriterGuid;

    //��Ӧ�Ķ��Ķ�
    StatefulReader *m_pRelatedReader;

    //������ַ�б�
    _LOCATOR_LIST_T m_UnicastLocatorList;

    //�ಥ��ַ�б�
    _LOCATOR_LIST_T m_MulticastLocatorList;

    //�ӷ����˽��յ����� ״̬�б�
    _CHANGE_FROM_WRITER_LIST_T m_ChangesFromWriter;

    //��һ����������ظ�Heartbeat���ĵ�ʱ��
    _TIME_T m_NextHeartbeatAllowedTime;

    //��һ����DDS DataReader�ύ���ݵ�ʱ��
    _TIME_T m_DataNotifyTime;

    //��һ�η���AckNack���ĵ�ʱ�䣨��ӦHeartbeat��
    _TIME_T m_NextAckNackTime;

    //�����һ�ν��յ�Heartbeat�������
    _COUNT_T m_HeartbeatLastCount;

    //��һ�η���AckNack�����
    _COUNT_T m_AcknowledgedStatusCount;

    //������DDS DataReader�ύ��������к�
    _SEQUENCE_NUMBER_T m_HighestSeqNumAvailable;

    //�Ѿ���DDS DataReader�ύ�����ݵ�������к�
    _SEQUENCE_NUMBER_T m_HighestSeqnumNotify;

	//2014-02-28 hjy modify �������͵�Ack����,ÿ50�����һ��,Ȼ������
	unsigned long SendAckCount;

    //������ �������m_ChangesFromWriter��m_HighestSeqNumAvailable��m_DataNotifyTime
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

};

#endif
