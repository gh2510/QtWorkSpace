/************************************************************
** �ļ�����SubscriptionsDataManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-22
** �޸��ˣ���
** ��  �ڣ���
** ��  ����SubscriptionsDataManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_SUBSCRIPTIONSDATAMANAGER_H_INCLUDED_
#define _RTPS_SUBSCRIPTIONSDATAMANAGER_H_INCLUDED_

#ifdef VXWORKS
#include "BasicTypes.h"
#include "ReturnCode.h"
#include <taskLib.h>
#include <sysLib.h>
#include <sockLib.h>
#else
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "windows.h"
#include <time.h>
#endif

class DomainParticipant;
class DataWriter;
class Participant;

class SubscriptionsDataManager
{
public:
    SubscriptionsDataManager(DomainParticipant *pDomainParticipant);

    virtual ~SubscriptionsDataManager();

    //�ж��Ƿ����µ�DataReader
    bool IsNewDataReader(_DISCOVERED_READER_DATA *pData);

    //����ReaderProxy
    //���յ�һ��Զ��DataReader���½���Ϣ�������뱾�����е�DataWriterƥ�䣬����ReaderProxy
    _RETURNCODE_T ReaderProxyConfigure(
        _DISCOVERED_READER_DATA* pData);

    //����ReaderProxy
    //�����½���һ��DataWriter������������Զ�˵�DataReader��Ϣƥ�䣬����ReaderProxy
    _RETURNCODE_T ReaderProxyConfigure(
        DataWriter* pDataWriter);

    //ɾ��ReaderProxy
    //���յ�Զ�˵�DataReader��ɾ����Ϣ���ڱ�������DataWriter��ReaderProxy��Ѱ������Ϣ��ɾ��
    _RETURNCODE_T ReaderProxyRemove(
        _DISCOVERED_READER_DATA* pData);

    //����
    _RETURNCODE_T AddRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteDataReader(_SUBSCRIPTIONS_DATA_LIST_T::iterator itData);
    //����
    _RETURNCODE_T RefreshRemoteDataReader(_DISCOVERED_READER_DATA *pData);
    //����
    _RETURNCODE_T RefreshRemoteDataReader(
        _DISCOVERED_READER_DATA *pData1,
        _DISCOVERED_READER_DATA *pData2);

    //Զ�˵�Participant��ʱ ɾ����������DataReader
    _RETURNCODE_T RemoteParticipantTimeout(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

	//����Զ�˷�����Ϣ�б�
	_SUBSCRIPTIONS_DATA_LIST_T RemoteSubscriptionsList() 
    {
		return m_pRemoteSubscriptionsList;
	}

	//���Է�������ƥ��ʱ��ר�� ����ƥ��Discovery�����DataReader����  2013-09-09 ������
	unsigned long GetDiscoveryMatchDataReaderNumber()
	{
		return m_DiscoveryMatchDataReaderNumber;
	}

	//���Է�������ƥ��ʱ��ר�� ����ƥ��Discovery�����DataReader����  2013-09-09 ������
	void AddDiscoveryMatchDataReaderNumber()
	{
		m_DiscoveryMatchDataReaderNumber++;
	}

	//���Է�������ƥ��ʱ��ר�� �趨ƥ��Discovery�����DataReader�ܸ���  2013-09-09 ������
	void SetDiscoveryMatchTotalDataReaderNumber(unsigned long TotalNumber)
	{
		m_DiscoveryMatchTotalDataReaderNumber = TotalNumber;
	}

	//���Է�������ƥ��ʱ��ר�� ����ƥ��Discovery�����DataReader�ܸ���  2013-09-09 ������
	unsigned long GetDiscoveryMatchTotalDataReaderNumber()
	{
		return m_DiscoveryMatchTotalDataReaderNumber;
	}

#ifdef VXWORKS
		//���Է�������ƥ��ʱ��ר�� ����DataWriter֮ǰʱ��  2013-09-09 ������
		void SetDiscoveryBeginTime()
		{
			clock_gettime(CLOCK_REALTIME, &m_DiscoveryBeginTime);
		}

		//���Է�������ƥ��ʱ��ר�� �����յ�N��DataReader֮���ʱ��  2013-09-09 ������
		void SetDiscoveryEndTime()
		{
			clock_gettime(CLOCK_REALTIME, &m_DiscoveryEndTime);
		}
		
		//���Է�������ƥ��ʱ��ר�� �����յ�N��DataReader֮���ʱ��  2013-09-09 ������
		double GetDiscoveryTime()
		{
			return (double)(m_DiscoveryEndTime.tv_sec + m_DiscoveryEndTime.tv_nsec*0.000000001 - m_DiscoveryBeginTime.tv_sec - m_DiscoveryBeginTime.tv_nsec*0.000000001 );
		}
#else
		//���Է�������ƥ��ʱ��ר�� ����DataWriter֮ǰʱ��  2013-09-09 ������
		void SetDiscoveryBeginTime()
		{
			QueryPerformanceCounter(&m_DiscoveryBeginTime);
		}

		//���Է�������ƥ��ʱ��ר�� �����յ�N��DataReader֮���ʱ��  2013-09-09 ������
		void SetDiscoveryEndTime()
		{
			QueryPerformanceFrequency(&m_DiscoveryFrequence);
			QueryPerformanceCounter(&m_DiscoveryEndTime);
		}
		
		//���Է�������ƥ��ʱ��ר�� �����յ�N��DataReader֮���ʱ��  2013-09-09 ������
		double GetDiscoveryTime()
		{
			return (double)(m_DiscoveryEndTime.QuadPart-m_DiscoveryBeginTime.QuadPart)/(double)m_DiscoveryFrequence.QuadPart;
		}
#endif
	

private:
    //���ڵ�DomainParticipant
    DomainParticipant *m_pDomainParticipant;
    //Զ��DataReader��Ϣ����
    _SUBSCRIPTIONS_DATA_LIST_T m_pRemoteSubscriptionsList;

    //����
    _SUBSCRIPTIONS_DATA_LIST_T::iterator LookupRemoteDataReader(
        _DISCOVERED_READER_DATA *pData);

    //�ж��Ƿ���ͬһ��DataReader
    bool IsSameDataReader(
        _DISCOVERED_READER_DATA *pData1,
        _DISCOVERED_READER_DATA *pData2);

    //ΪDataWriter��ƥ�� ����ReaderProxy
    bool MatchDataWriter(
        DataWriter *pDataWriter,
        _DISCOVERED_READER_DATA *pData);

    //�ж�DataReader�Ƿ�����Participant
    bool Belong(_DISCOVERED_READER_DATA *pReaderData,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pParticipantData);
	bool Belong(_DISCOVERED_READER_DATA *pReaderData,
        Participant *aParticipant);
	
#ifdef VXWORKS
		//���Է�������ƥ��ʱ��ר�� ����DataWriter֮ǰʱ���  2013-09-09 ������
		struct timespec m_DiscoveryBeginTime;

		//���Է�������ƥ��ʱ��ר�� �յ�N��DataReader֮��ʱ���  2013-09-09 ������
		struct timespec m_DiscoveryEndTime;

#else
		//���Է�������ƥ��ʱ��ר�� ����DataWriter֮ǰʱ���  2013-09-09 ������
		LARGE_INTEGER m_DiscoveryBeginTime;

		//���Է�������ƥ��ʱ��ר�� �յ�N��DataReader֮��ʱ���  2013-09-09 ������
		LARGE_INTEGER m_DiscoveryEndTime;

		//���Է�������ƥ��ʱ��ר�� �յ�N��DataReader֮��ʱ���  2013-09-09 ������
		LARGE_INTEGER m_DiscoveryFrequence;

#endif
	
	//���Է�������ƥ��ʱ��ר�� ƥ��Discovery�����DataReader����  2013-09-09 ������
	unsigned long m_DiscoveryMatchDataReaderNumber;

	//���Է�������ƥ��ʱ��ר�� ƥ��Discovery�����DataReader���ܸ���  2013-09-09 ������
	unsigned long m_DiscoveryMatchTotalDataReaderNumber;


    //������
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
