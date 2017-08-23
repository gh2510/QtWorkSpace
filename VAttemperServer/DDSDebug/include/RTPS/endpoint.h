/************************************************************
** �ļ�����Endpoint.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-10
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Endpointͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_ENDPOINT_H_INCLUDED_
#define _RTPS_ENDPOINT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RTPSEntity.h"

struct _ACKNACK_SUBMESSAGE;
struct _HEARTBEAT_SUBMESSAGE;
struct _DATA_SUBMESSAGE;
struct _DATA_FRAG_SUBMESSAGE;
struct _NACK_FRAG_SUBMESSAGE;

class Endpoint : public RTPSEntity 
{
public:
    //���캯��
    Endpoint ( _GUID_T Guid,
        _RELIABILITY_KIND_T ReliabilityLevel,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList) :
    RTPSEntity (Guid) 
    {
        //��ʼ�� ��ֵ
        m_ReliabilityLevel = ReliabilityLevel;
        m_UnicastLocatorList = UnicastLocatorList;
        m_MulticastLocatorList = MulticastLocatorList;
    }

    //��������
    virtual ~Endpoint () 
    {
        m_UnicastLocatorList.clear();
        m_MulticastLocatorList.clear();
    };

    //�麯�� �ṩ���Ľ��սӿ� ������
    //����AckNack����
    virtual _RETURNCODE_T AckNackMessageReceive(
        _ACKNACK_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    //����Heartbeat����
    virtual _RETURNCODE_T HeartbeatMessageReceive(
        _HEARTBEAT_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

	//����Data����
    virtual _RETURNCODE_T DataMessageReceive(
        _DATA_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    //����DataFrag����
    virtual _RETURNCODE_T DataFragMessageReceive(
		_DATA_FRAG_SUBMESSAGE *pMessage, 
		_RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

	//����NackFrag����
    virtual _RETURNCODE_T NackFragMessageReceive(
		_NACK_FRAG_SUBMESSAGE *pMessage, 
		_RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    virtual _TIME_T Deadline() 
    {
        return TIME_INFINITE;
    }

    //�麯�� ���Deadline QoS�Ľӿ�
    virtual _RETURNCODE_T DeadlineCheck() 
    {
        return RETURNCODE_OK;
    };

    //��ȡ������ַ�б�
    _LOCATOR_LIST_T UnicastLocatorListGet()
    {
        return m_UnicastLocatorList;
    }

    //��ȡ�ಥ��ַ�б�
    _LOCATOR_LIST_T MulticastLocatorListGet()
    {
        return m_MulticastLocatorList;
    }

    //��ȡһ��Ĭ�ϵ�����ַ
    _LOCATOR_T UnicastLocatorGet() 
    {
        if (m_UnicastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        //cout<<"Uni get:"<<m_UnicastLocatorList[0].ulAddress<<" "<<m_UnicastLocatorList[0].ulPort<<endl;
        return m_UnicastLocatorList[0];
    }

    //��ȡһ��Ĭ�϶ಥ��ַ
    _LOCATOR_T MulticastLocatorGet() 
    {
        if (m_MulticastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_MulticastLocatorList[0];
    }

    //��ȡ�˵�Ŀɿ��̶�
    _RELIABILITY_KIND_T ReliabilityKind() 
    {
        return m_ReliabilityLevel;
    }

protected:
    //�ɿ��̶�
    _RELIABILITY_KIND_T m_ReliabilityLevel;

    //������ַ�б�
    _LOCATOR_LIST_T m_UnicastLocatorList;

    //�ಥ��ַ�б�
    _LOCATOR_LIST_T m_MulticastLocatorList;

    //�������ͣ��Ƿ��м�
    _TOPIC_KIND_T m_TopicKind;
};

#endif
