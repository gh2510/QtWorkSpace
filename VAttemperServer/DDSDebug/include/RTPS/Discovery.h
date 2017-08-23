/************************************************************
** �ļ�����Discovery.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-13
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Discoveryͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_DISCOVERY_H_INCLUDE_
#define _RTPS_DISCOVERY_H_INCLUDE_

#include "BasicTypes.h"
#include "ReturnCode.h"

class DomainParticipant;

class BuiltinPariticipantWriterListener;
class BuiltinPariticipantReaderListener;
class BuiltinPublicationsReaderListener;
class BuiltinSubscriptionsReaderListener;

class Topic;
class DataWriter;
class DataReader;

class ParticipantDataWriter;
class ParticipantDataReader;
class PublicationsDataWriter;
class PublicationsDataReader;
class SubscriptionsDataWriter;
class SubscriptionsDataReader;

class Discovery{
public:
    Discovery(DomainParticipant* pParticipant);

    virtual ~Discovery();

    //��ʼ������ģ��Ķ˵� ĿǰΪ6�����ö˵�
    _RETURNCODE_T DiscoveryInitiation(_DURATION_T ResendPeriod);
    //ɾ�����ö˵�
    _RETURNCODE_T DiscoveryRelease();

    //�㲥��Participant��Ϣ
    _RETURNCODE_T SendLocalParticipant();

    //�㲥��Participant�˳�����Ϣ
    _RETURNCODE_T NotifyParticipantLogoff();

    //�����û�����ķ����˵���Ϣ
    _RETURNCODE_T SendPublicationData(
        DataWriter* pDataWriter,
        _ENTITY_STATUS_T Status);

    //�����û�����Ķ��Ķ˵���Ϣ
    _RETURNCODE_T SendSubscriptionData(
        DataReader* pDataReader,
        _ENTITY_STATUS_T Status);

    //ƥ��DataReader
    //�����½�DataReader�����
    _RETURNCODE_T MatchDataReader(DataReader *pDataReader);

    //ƥ��DataWriter
    //�����½�DataWriter�����
    _RETURNCODE_T MatchDataWriter(DataWriter *pDataWriter);

public:
    //��ȡ������DomainParticipant
    DomainParticipant* GetRelatedParticipant() 
    {
        return m_pDomainParticipant;
    }

    //��ȡ���ö˵�
    ParticipantDataWriter *GetParticipantDataWriter() 
    {
        return m_pBuiltinParticipantDataWriter;
    }
    ParticipantDataReader *GetParticipantDataReader() 
    {
        return m_pBuiltinParticipantDataReader;
    }
    PublicationsDataWriter *GetPublicationsDataWriter() 
    {
        return m_pBuiltinPublicationsDataWriter;
    }
    PublicationsDataReader *GetPublicationsDataReader() 
    {
        return m_pBuiltinPublicationsDataReader;
    }
    SubscriptionsDataWriter *GetSubscriptionsDataWriter() 
    {
        return m_pBuiltinSubscriptionsDataWriter;
    }
    SubscriptionsDataReader *GetSubscriptionsDataReader() 
    {
        return m_pBuiltinSubscriptionsDataReader;
    }

private:
    //�������õĶ˵�
    _RETURNCODE_T BuiltinEntityCreation(
        _DURATION_T ResendPeriod,
        _DURATION_T LeaseDuration);
    //��������
    _RETURNCODE_T CreateParticipantTopic();
    _RETURNCODE_T CreatePublicationsTopic();
    _RETURNCODE_T CreateSubscriptionsTopic();
    //�������÷�����
    _RETURNCODE_T CreateParticipantDataWriter(
        _DURATION_T ResendPeriod,
        _DURATION_T LeaseDuration);
    _RETURNCODE_T CreatePublicationsDataWriter();
    _RETURNCODE_T CreateSubscriptionsDataWriter();
    //�������ö�����
    _RETURNCODE_T CreateParticipantDataReader();
    _RETURNCODE_T CreatePublicationsDataReader();
    _RETURNCODE_T CreateSubscriptionsDataReader();

private:
    //������DomainParticipant
    DomainParticipant* m_pDomainParticipant;


	//DDS�����ö˵�
	//2013-10-15 hjy modify ɾ�����ýڵ�ר��
	DataWriter* m_pParticipantDataWriter;
	DataWriter* m_pPublicationsDataWriter;
	DataWriter* m_pSubscriptionsDataWriter;

	DataReader* m_pParticipantDataReader;
	DataReader* m_pPublicationsDataReader;
	DataReader* m_pSubscriptionsDataReader;

    //DDS�����ö˵�
    ParticipantDataWriter* m_pBuiltinParticipantDataWriter;
    PublicationsDataWriter* m_pBuiltinPublicationsDataWriter;
    SubscriptionsDataWriter* m_pBuiltinSubscriptionsDataWriter;

    ParticipantDataReader* m_pBuiltinParticipantDataReader;
    PublicationsDataReader* m_pBuiltinPublicationsDataReader;
    SubscriptionsDataReader* m_pBuiltinSubscriptionsDataReader;

    //��������
    Topic* m_pDcpsParticipantTopic;
    Topic* m_pDcpsPublicationsTopic;
    Topic* m_pDcpsSubscriptionsTopic;
};

#endif
