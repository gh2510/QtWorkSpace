/************************************************************
** �ļ�����HistoricGatherManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-03-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����HistoricGatherManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICGATHERMANAGER_H_INCLUDED_
#define _API_HISTORICGATHERMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#include "Windows.h"
#endif

class DomainParticipant;
struct _DISCOVERED_WRITER_DATA;
class DynamicDataReader;
class HistoricRepublishManager;
class DataBaseManager;

#pragma warning(disable:4251)

struct _DYNAMIC_READER_RECORD
{
	DynamicDataReader* pHistoricReader;
	DomainParticipant* pDomainParticipant;
	unsigned long ulCount;
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class HistoricGatherManager 
{
#else
class DDS_DLL HistoricGatherManager 
{
#endif
public:
	//���HistoricGatherManager����
    static HistoricGatherManager* Get_Instance();

	//����HistoricGatherManager����
    static HistoricGatherManager* Create_Instance(list<unsigned long> DomainIDList);

	//��鷢�ֵķ�����Ϣ���Գ־��Է���������Ӧ���Ķˡ���ʷ�����ط�����
    _RETURNCODE_T DiscoverNewPublish (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//���ֶ���ɾ����Ϣ��ɾ����Ӧ���Ķ�
	_RETURNCODE_T DiscoverPublishDeletion (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//������ʷ���ݶ��Ķˣ���ʼ��ʷ���ݽ���
	DynamicDataReader* CreateHistoryDynamicDataReader (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//ɾ����ʷ���ݶ��Ķˣ�ֹͣ��ʷ���ݽ���
	_RETURNCODE_T DeleteHistoryDynamicDataReader (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//������̬��������
	Topic* CreateHistoryDynamicTopic (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//ɾ����̬��������
	_RETURNCODE_T DeleteHistoryDynamicTopic (DomainParticipant* pDomainParticipant, _DISCOVERED_WRITER_DATA* pDiscoveredWriterData);

	//�����ʷ�����ط�����
	HistoricRepublishManager* GetHistoricRepublishManager()
    {
		return m_pRepublishManager;
	}

private:
	HistoricGatherManager();

	~HistoricGatherManager();

	//HistoricGatherManager������ָ��
    static HistoricGatherManager *m_pInstance;

	//DomainParticipant ָ���б�
    static list<DomainParticipant*> m_pDomainParticipantList;

	//��̬���Ķ��б�
	list<_DYNAMIC_READER_RECORD> m_HistoricDataDRList;

	//��ʷ���ݴ洢�����ָ��
	DataBaseManager* m_pDataBaseManager;

	//��ʷ�����ط��������ߵ�ָ��
	HistoricRepublishManager* m_pRepublishManager;

	//Ӧ����
	static char* m_pCompName;

	//������
#ifdef VXWORKS   //��ֲ
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
