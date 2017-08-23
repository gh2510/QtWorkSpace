/************************************************************
** �ļ�����ReaderProxy.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-12
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ReaderProxyͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef RTPS_READERPROXY_INCLUDED_H
#define RTPS_READERPROXY_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Message.h"

#ifdef VXWORKS
#include <semLib.h>
#else
#include "Windows.h"
#endif

class StatefulWriter;
class HistoryCache;

class ReaderProxy
{
public:
    //���캯��
    ReaderProxy( _GUID_T ReaderGuid,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        StatefulWriter* pStatefulWriter);

    //��������
    virtual ~ReaderProxy();

    //���_CHANGE_FOR_READER����
    _CHANGE_FOR_READER* ChangeForReaderAdd( _CACHE_CHANGE* pCacheChange );

    //ɾ��_CHANGE_FOR_READER����
    _RETURNCODE_T ChangeForReaderRemove( _CACHE_CHANGE* pCacheChange );

    //����ָ����_CHANGE_FOR_READER����
    _CHANGE_FOR_READER* ChangeForReaderLookup( _SEQUENCE_NUMBER_T SeqNum);

    //��ȡ��ReaderProxy�����Զ�˶��Ķ˵��GUID
    _GUID_T ReaderGuid();

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

    //���ñ�ȷ�ϵ�Changes
    _RETURNCODE_T AckedChangesSet( _SEQUENCE_NUMBER_T CommittedSeqNum);

    //���ñ������Changes
    _RETURNCODE_T RequestedChangesSet( _SEQUENCE_NUMBER_SET* pReqSeqNumSet);

    //������һ��Ҫ���͵�_CACHE_CHANGE
    _CACHE_CHANGE* NextUnsentChange();

    //�������к���С�ı������_CACHE_CHANGE
    _CACHE_CHANGE* NextRequestedChange();

    //��ѯָ�����кŵ�_CACHE_CHANGE�Ƿ�ȷ��
    bool IsAcked( _SEQUENCE_NUMBER_T SeqNum);

    //��ѯ�Ƿ���δȷ�ϵ�_CACHE_CHANGE
    bool UnsentChanges();

    //��ѯ�Ƿ���δ�����_CACHE_CHANGE
    bool RequestedChanges();

    //��ѯ�Ƿ���δ��ȷ�ϵ�_CACHE_CHANGE
    bool UnackedChanges();

    //���Է��͹����AckNack����
    bool AckNackIgnore( _COUNT_T AckNackCount);

    //�����´��ط�Data���ĵ�ʱ��
    _TIME_T NextDataRepairTime();

	//�����ط�Data���ĵ�ʱ��
	_RETURNCODE_T SetRepairTime();

	//�����´ο��Խ���Nack��ʱ��
	_RETURNCODE_T SetNackAllowedTime();

    //���ý��յ�AckNack���ı��
    _RETURNCODE_T SetAckNackLastCount (_COUNT_T Count) 
    {
        m_AckNackLastCount = Count;

        return RETURNCODE_OK;
    }

    _SEQUENCE_NUMBER_T HighestSeqNumAcked() 
    {
        return m_HighestSeqNumAcked;
    }

    //�Ƿ���ڶಥ��ַ
    bool MulticastExist() 
    {
        if (m_MulticastLocatorList.size() == 0)
            return false;
        return true;
    }

private:
    //Զ�˶��Ķ˵��GUID
    _GUID_T              m_RemoteReaderGuid;

    //��Ӧ��StatefulWriter
    StatefulWriter      *m_pRelatedWriter;

    //Զ�˶��Ķ˵�����ַ�б�
    _LOCATOR_LIST_T         m_UnicastLocatorList;

    //Զ�˶��Ķ˶ಥ��ַ�б�
    _LOCATOR_LIST_T         m_MulticastLocatorList;

    //ReaderProxy��_CHANGE_FOR_READER�б�
    _CHANGE_FOR_READER_LIST m_ChangesForReaderList;//�޸�

    //
    bool                m_bIsActive;

    //������յ���AckNack���ĵ����к�
    _COUNT_T             m_AckNackLastCount;

    //�ѷ���_CACHE_CHANGE��������к�
    _SEQUENCE_NUMBER_T    m_HighestSeqNumSent;

    //�ѱ�ȷ�ϵ�_CACHE_CHANGE��������к�
    _SEQUENCE_NUMBER_T    m_HighestSeqNumAcked;

    //��һ�ο��Խ���Nack��ʱ��
    _TIME_T              m_NextNackAllowedTime;

    //�´��ط�Data���ĵ�ʱ��
    _TIME_T              m_NextRepairTime;

    //������ �������m_changesForReader��m_NextRepairTime
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
