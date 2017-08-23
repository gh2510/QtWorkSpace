/************************************************************
** �ļ�����HistoricRepublishManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-03-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����HistoricRepublishManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICREPUBLISHMANAGER_H_INCLUDED_
#define _API_HISTORICREPUBLISHMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#include "Windows.h"
#endif

#pragma warning(disable:4251)

class DomainParticipant;
struct _DISCOVERED_WRITER_DATA;
struct _DISCOVERED_READER_DATA;
class DynamicDataWriter;

struct _DYNAMIC_WRITERRECORD
{
	DynamicDataWriter* pHistoricWriter;
	//DomainParticipant* pDomainParticipant;
	//unsigned long count;
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class HistoricRepublishManager 
{
#else
class DDS_DLL HistoricRepublishManager 
{
#endif
public:
	//���HistoricRepublishManager����
    static HistoricRepublishManager* Get_Instance();

	//������ʷ���ݷ����ˣ���ʼ��ʷ���ݷ���
	DynamicDataWriter* CreateHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//������ʷ���ݷ����ˣ���ʼ��ʷ���ݷ���
	DynamicDataWriter* CreateHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, const char* pTopicName, const char* pTypeName, _ENTITY_QOS* pQos);

	//ɾ����ʷ���ݷ����ˣ�ֹͣ��ʷ���ݷ���
	_RETURNCODE_T DeleteHistoryDynamicDataWriter (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//������̬��������
	Topic* CreateHistoryDynamicTopic (DomainParticipant* pDomainParticipant, const char* pTopicName, const char* pTypeName);

	//ɾ����̬��������
	_RETURNCODE_T DeleteHistoryDynamicTopic (DomainParticipant* pDomainParticipant, char* pTopicName, char* pTypeName);

	//��鷢�ֵĶ�����Ϣ���Գ־��Զ��ģ���ȡ��ʷ���ݷ���
	_RETURNCODE_T DiscoverNewSubscribe (DomainParticipant* pDomainParticipant, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

	//�������⡢pQos���Ҷ�Ӧ������
	DynamicDataWriter* GetHistoryDynamicDataWriter (unsigned long ulDomainId, const char* pTopicName, const char* pTypeName, _ENTITY_QOS* pQos);

	//������ʷ����
	_RETURNCODE_T SendHistoricData(DomainParticipant* pDomainParticipant, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

private:
	HistoricRepublishManager() {}
	~HistoricRepublishManager() {}

	//������ָ��
    static HistoricRepublishManager *m_pInstance;

	//Ӧ����
	static char* m_pCompName;

	//��̬�������б�
	list<_DYNAMIC_WRITERRECORD> m_HISTORIC_DATADWLIST;

	//������
#ifdef VXWORKS   //��ֲ
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
