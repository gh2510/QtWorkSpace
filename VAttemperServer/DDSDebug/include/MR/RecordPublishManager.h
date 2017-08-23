/************************************************************
** �ļ�����RecordPublishManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����RecordPublishManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef RecordPublishManager_hh
#define RecordPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class RecordInfoSendListDataWriter;
class MonitorRecordAgent;

class RecordPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//����������Ϣ��DataWriter
	RecordInfoSendListDataWriter *m_pDataWriter;
	//����
	Topic *m_pTopic;
	//�����ָ��
	MonitorRecordAgent *m_pAgent;

	//��ʱ�洢����
	int m_iCounter;

//�洢β�������߳������
#ifdef VXWORKS  
	int m_hTaskId;
#else
	HANDLE m_hTaskId;
#endif

	//����״̬��Ϣ��ʱ�б�
	_RECORD_INFO m_pRecordInfo[122];

	//������
#ifdef VXWORKS   
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

public:
	//���캯��
	RecordPublishManager(MonitorRecordAgent *pAgent);             //RecordPublishManager.h
	//��������
	~RecordPublishManager();             //RecordPublishManager.h

	//����RecordInfoSendListDataWriter
	_RETURNCODE_T CreateRecordInfoSendListDW(void);           //RecordPublishManager.h
	//��������
	_RETURNCODE_T CreateRecordInfoSendListTopic(void);         //RecordPublishManager.h
	//����������Ϣ
	_RETURNCODE_T SendRecordInfo(_RECORD_INFO* pData);           //RecordPublishManager.h

#ifdef VXWORKS
	static _RETURNCODE_T SendRun(RecordPublishManager* pRecordPublishManager);
#else
	static DWORD WINAPI SendRun(RecordPublishManager* pRecordPublishManager);         //RecordPublishManager.h
#endif

	_RETURNCODE_T Send();        //RecordPublishManager.h
	//ɾ������
	_RETURNCODE_T DeleteRecordInfoSendListTopic(void);           //RecordPublishManager.h
	//ɾ��RecordInfoSendListDataWriter
	_RETURNCODE_T  DeleteRecordInfoSendListDW(void);           //RecordPublishManager.h

};

#endif
