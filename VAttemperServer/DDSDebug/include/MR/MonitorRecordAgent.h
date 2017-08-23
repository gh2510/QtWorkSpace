/************************************************************
** �ļ�����MonitorRecordAgent.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-07-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MonitorRecordAgentͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef MonitorRecordAgent_hh
#define MonitorRecordAgent_hh
#include"MRBasicTypes.h"
#include "MRReturnCode.h"

#ifdef VXWORKS 
#include <semLib.h>
#else
#include "Windows.h" 
#endif

#include "string"
using std::string;
class DomainParticipant;
class NodePublishManager;
class CompPublishManager;
class TopicPublishManager;
class RecordPublishManager;
class LocalDataGather;

#ifdef VXWORKS
class MonitorRecordAgent 
{
private:
	//DomainParticipantָ��
	DomainParticipant *m_pDDSParticipant;
	//������Ϣ�Ѽ���ָ��
	LocalDataGather *m_pLocalDataGather;
	//�ڵ�״̬��Ϣ����������ָ��
	NodePublishManager *m_pNodePublicationManager;
	//���״̬��Ϣ������ָ��
	CompPublishManager *m_pCompPublicationManager;
	//��Ϣ״̬��Ϣ������ָ��
	TopicPublishManager *m_pTopicPublicationManager;
	//����״̬��Ϣ������ָ��
	RecordPublishManager *m_pRedordPublicationManager;

	//�ڵ�״̬��Ϣ
	_NODE_INFO* m_pNodeInfo;
	//���״̬��Ϣ
	_COMP_INFO* m_pCompInfo;

	//������
	SEM_ID m_hSemNodeInfoMutex;
	SEM_ID m_hSemCompInfoMutex;
	SEM_ID m_hSemTopicInfoMutex;
	SEM_ID m_hSemRecordInfoMutex;

public:
	//��¼�����߳�
 	int m_hRecordSendTaskId;

	//���캯��,������ػ��¼
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, int iTaskId, char* pCompName, int iMONITOR, int iRECORD);    //MonitorRecordAgent.h
	//��������
	~MonitorRecordAgent (void);	
	//��ʼ��������������غͼ�¼
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, int iTaskId,char* pCompName);    //MonitorRecordAgent.h
	//��ʼ���������������
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, int iTaskId,char* pCompName);   //MonitorRecordAgent.h


	//��ʼ������������
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);   //MonitorRecordAgent.h

	//��ȡDomainParticipantָ��
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}      //MonitorRecordAgent.h

	//���ͽڵ�״̬��Ϣ
	_RETURNCODE_T  SendNodeInfo(void);       //MonitorRecordAgent.h
	//�������״̬��Ϣ
	_RETURNCODE_T SendCompInfo(void);        //MonitorRecordAgent.h
	//������Ϣ��״̬��Ϣ
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);     //MonitorRecordAgent.h
	//��������״̬��Ϣ
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);  //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();      //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();         //MonitorRecordAgent.h

};

#else

#ifdef _DDS_LIB_FILE

class MonitorRecordAgent
{
private:
	//DomainParticipantָ��
	DomainParticipant *m_pDDSParticipant;
	//������Ϣ�Ѽ���ָ��
	LocalDataGather *m_pLocalDataGather;
	//�ڵ�״̬��Ϣ����������ָ��
	NodePublishManager *m_pNodePublicationManager;
	//���״̬��Ϣ������ָ��
	CompPublishManager *m_pCompPublicationManager;
	//��Ϣ״̬��Ϣ������ָ��
	TopicPublishManager *m_pTopicPublicationManager;
	//����״̬��Ϣ������ָ��
	RecordPublishManager *m_pRedordPublicationManager;

	//�ڵ�״̬��Ϣ
	_NODE_INFO* m_pNodeInfo;
	//���״̬��Ϣ
	_COMP_INFO* m_pCompInfo;

	//������
	HANDLE m_hSemNodeInfoMutex;
	HANDLE m_hSemCompInfoMutex;
	HANDLE m_hSemTopicInfoMutex;
	HANDLE m_hSemRecordInfoMutex;


public:
	//��¼�����߳�
	HANDLE m_hRecordSendTaskId;


	//���캯��,������ػ��¼
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, HANDLE iTaskId, char* pCompName, int iMONITOR, int iRECORD);        //MonitorRecordAgent.h
	//��������
	~MonitorRecordAgent (void);	        //MonitorRecordAgent.h
	//��ʼ��������������غͼ�¼
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);     //MonitorRecordAgent.h
	//��ʼ���������������
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);     //MonitorRecordAgent.h


	//��ʼ������������
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);        //MonitorRecordAgent.h

	//��ȡDomainParticipantָ��
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}             //MonitorRecordAgent.h

	//���ͽڵ�״̬��Ϣ
	_RETURNCODE_T  SendNodeInfo(void);          //MonitorRecordAgent.h
	//�������״̬��Ϣ
	_RETURNCODE_T SendCompInfo(void);           //MonitorRecordAgent.h
	//������Ϣ��״̬��Ϣ
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);       //MonitorRecordAgent.h
	//��������״̬��Ϣ
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);         //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();        //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();            //MonitorRecordAgent.h

};

#else

class DDS_DLL MonitorRecordAgent
{
private:
	//DomainParticipantָ��
	DomainParticipant *m_pDDSParticipant;
	//������Ϣ�Ѽ���ָ��
	LocalDataGather *m_pLocalDataGather;
	//�ڵ�״̬��Ϣ����������ָ��
	NodePublishManager *m_pNodePublicationManager;
	//���״̬��Ϣ������ָ��
	CompPublishManager *m_pCompPublicationManager;
	//��Ϣ״̬��Ϣ������ָ��
	TopicPublishManager *m_pTopicPublicationManager;
	//����״̬��Ϣ������ָ��
	RecordPublishManager *m_pRedordPublicationManager;

	//�ڵ�״̬��Ϣ
	_NODE_INFO* m_pNodeInfo;
	//���״̬��Ϣ
	_COMP_INFO* m_pCompInfo;

	//������
	HANDLE m_hSemNodeInfoMutex;
	HANDLE m_hSemCompInfoMutex;
	HANDLE m_hSemTopicInfoMutex;
	HANDLE m_hSemRecordInfoMutex;


public:
	//��¼�����߳�
	HANDLE m_hRecordSendTaskId;


	//���캯��,������ػ��¼
	MonitorRecordAgent(DomainParticipant *pDDSParticipant, HANDLE iTaskId, char* pCompName, int iMONITOR, int iRECORD);      //MonitorRecordAgent.h
	//��������
	~MonitorRecordAgent (void);	
	//��ʼ��������������غͼ�¼
	_RETURNCODE_T InitializeBoth(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);         //MonitorRecordAgent.h
	//��ʼ���������������
	_RETURNCODE_T InitializeMonitor(DomainParticipant *pDDSParticipant, HANDLE iTaskId,char* pCompName);          //MonitorRecordAgent.h


	//��ʼ������������
	_RETURNCODE_T InitializeRecord(DomainParticipant *pDDSParticipant);        //MonitorRecordAgent.h

	//��ȡDomainParticipantָ��
	DomainParticipant* GetParticipant()
	{
		return m_pDDSParticipant;
	}              //MonitorRecordAgent.h

	//���ͽڵ�״̬��Ϣ
	_RETURNCODE_T  SendNodeInfo(void);       //MonitorRecordAgent.h
	//�������״̬��Ϣ
	_RETURNCODE_T SendCompInfo(void);       //MonitorRecordAgent.h
	//������Ϣ��״̬��Ϣ
	_RETURNCODE_T SendTopicInfo(char* pCompName,char* pTopicName,char* pTypeName,char* pTypeCode,unsigned long ulDomainId, _TOPIC_STATUS TopicStatus);        //MonitorRecordAgent.h
	//��������״̬��Ϣ
	_RETURNCODE_T SendRecordInfo(unsigned long ulDomainId, char * pCompName, char *pTopicName, _TIMESTAMP_T Timestamp, _ACTION_KIND ActionKind, _SEQUENCE_NUM Seqnum);        //MonitorRecordAgent.h

	_RETURNCODE_T StartMonitor();        //MonitorRecordAgent.h
	_RETURNCODE_T StartRecord();        //MonitorRecordAgent.h
};
#endif
#endif

#endif

