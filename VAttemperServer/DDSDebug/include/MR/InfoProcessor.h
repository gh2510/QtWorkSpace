/************************************************************
** �ļ�����InfoProcessor.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-22
** �޸��ˣ���
** ��  �ڣ���
** ��  ����InfoProcessorͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _INFOPROCESSOR_H
#define _INFOPROCESSOR_H
#include"MRBasicTypes.h"
#include "MRReturnCode.h"

#include"DDS/DomainParticipant.h"

#ifdef VXWORKS 
#include <semLib.h>
#else
#include "Windows.h" 
#include <io.h>
#endif

#include "TopicInfoDataReader.h"
#include "NodeInfoDataReader.h"
#include "CompInfoDataReader.h"
#include "RecordInfoSendListDataReader.h"
#include "DynamicDataReader.h"
#include "TopicInfoDRListener.h"
#include "NodeInfoDRListener.h"
#include "CompInfoDRListener.h"
#include "RecordInfoSendListDRListener.h"
#include "DynamicDRListener.h"
#include "SubscribeManager.h"

#ifdef VXWORKS
#include "SubscribeManager.h"
#else
class SubscribeManager;
#endif

class DomainParticipant;
class Topic;

class InfoProcessor
{
private:
	//�ڵ�ȫ��״̬��Ϣ�洢�ṹ
	_NODE_GINFO_MAP_T m_NodeInfoMap;
	//���ȫ��״̬��Ϣ�洢�ṹ
	_COMP_GINFO_MAP_T m_CompInfoMap;
	//����ȫ��״̬��Ϣ�洢�ṹ
	_TOPIC_GLOBAL_INFO_MAP_T m_TopicInfoMap;
	//����״̬��Ϣ��ʱ�洢�ṹ
	_RECORD_INFO_LIST m_RecordInfoSeq;

	//������ָ��
	static InfoProcessor* m_pProcessor;

#ifdef VXWORKS   
	//�����Ϣ�б�Ļ�����
	SEM_ID m_hSemCompWMutex;
	//������Ϣ�б�Ļ�����
	SEM_ID m_hSemTopicWMutex;
	//�ڵ���Ϣ�б�Ļ�����
	SEM_ID m_hSemNodeWMutex;
	//������Ϣ�ı��Ļ�����
	SEM_ID m_hSemRecordInfoWMutex;
#else
	//�����Ϣ�б�Ļ�����
	HANDLE m_hSemCompWMutex;
	//������Ϣ�б�Ļ�����
	HANDLE m_hSemTopicWMutex;
	//�ڵ���Ϣ�б�Ļ�����
	HANDLE m_hSemNodeWMutex;
	//������Ϣ�ı��Ļ�����
	HANDLE m_hSemRecordInfoWMutex;
#endif

	//���ݼ�¼
	//�洢β�������߳�/�����
#ifdef VXWORKS  
	int hTaskId;
#else
	HANDLE hTaskId;
#endif
	
public:
	//m_funcĬ��Ϊ0��m_func=1��Ϊ��أ�m_func=2��Ϊ��¼��m_func=3��Ϊ��ؼ�¼
	int m_iFunc;

	//��¼�ı�DRSRecord.txt RecordContent.txt���,��ʼΪ1
	//int m_DRSRecordTXTSeq;
	//int m_RecordContentTXTSeq;

	char m_szPathDRSRecordTXTtemp[100];
	char m_szPathRecordContentTXTtemp[100];

	list<_TOPIC_INFO> m_TopicInfoSeq;
	//���Ĺ�����ָ��
	SubscribeManager* m_pSubManager;

	_TIME_T m_MaxDiffTime;

	//����������ʵ��
	static InfoProcessor* CreateInstance(void);   //InfoProcessor.h
	//��ȡ������ʵ��
	static InfoProcessor* GetInstance(void);   //InfoProcessor.h
	
	static _RETURNCODE_T DeleteInstance(void);   //InfoProcessor.h

	//����ڵ�״̬��Ϣ
	_RETURNCODE_T ProcessNodeInfo(_NODE_INFO* pNodeInfo);   //InfoProcessor.h
	//�������״̬��Ϣ
	_RETURNCODE_T ProcessCompInfo(_COMP_INFO* pCompInfo);   //InfoProcessor.h
	//��������״̬��Ϣ
	_RETURNCODE_T ProcessTopicInfo(_TOPIC_INFO* pTopicInfo);   //InfoProcessor.h
	//����ͳ����Ϣ
	_RETURNCODE_T ProcessRecordInfo(_RECORD_INFO* pRecordInfo);  //InfoProcessor.h


	//��������״̬��Ϣ
	//�洢β�������߳�/������ں���
#ifdef VXWORKS
	static _RETURNCODE_T RecordStoreRun();   //InfoProcessor.h
#else
	static DWORD WINAPI RecordStoreRun();    //InfoProcessor.h
#endif

	//��ȡ�ڵ�״̬��Ϣ
	_RETURNCODE_T GetNodeInfo(unsigned long ulIpAddress,
												_NODE_GLOBAL_INFO &NodeGInfo);   //InfoProcessor.h
	//��ȡ���״̬��Ϣ
	_RETURNCODE_T GetCompInfo(unsigned long ulIpAddress, 
												string strComponentName,
												_COMP_GINFO& CompInfo);   //InfoProcessor.h
	//��ȡ����״̬��Ϣ
	_RETURNCODE_T GetTopicInfo(string strTopicName,
												unsigned long ulDomainId,
												_TOPIC_GLOBAL_INFO& TopicInfo);   //InfoProcessor.h

	_NODE_FIXED_INFO_TX_LIST GetNodeFixedInfoTXList();   //InfoProcessor.h
	_TOPIC_ID_TX_LIST GetTopicIDTXList();    //InfoProcessor.h

	//��ȡʱ��
	_TIMESTAMP_T DDSGetCurrentTime(void);   //InfoProcessor.h

	_RETURNCODE_T StartInfoProcessorMonitor(list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	_RETURNCODE_T StartInfoProcessorRecord(list<unsigned long> 	DomainIDList, list<string> TopicName);   //InfoProcessor.h
	_RETURNCODE_T ReleaseInfoProcessorMonitor();   //InfoProcessor.h
	_RETURNCODE_T ReleaseInfoProcessorRecord();   //InfoProcessor.h

	//��ȡ���¼������������
	_RETURNCODE_T GetRecordTopicNameList(list<string> pTopicName);   //InfoProcessor.h
	//��ȡ�ı���С
	//double getTXTsize(char* txtPath);
	//��ȡ��ǰ�ɼ�¼���ı�·��
	//char* getDRSRecordTXTPath();
	//fengjiaqi
	char* GetDBPath();   //InfoProcessor.h
    //fengjiaqi
	char* pPath;    //���ڱ������ݿ�·��

private: 
	//���캯��
	InfoProcessor(void)
	{
		m_iFunc = 0;
		//m_DRSRecordTXTSeq = getDRSRecordTxtSeq();
		//m_RecordContentTXTSeq = getRecordContentTxtSeq();
		hTaskId = 0;
		m_pSubManager = NULL;
		m_hSemCompWMutex = NULL;
		m_hSemTopicWMutex = NULL;
		m_hSemNodeWMutex = NULL;
		m_hSemRecordInfoWMutex = NULL;

		m_MaxDiffTime.ulNanosec = 0;
		m_MaxDiffTime.lSecond = 30;
		//fengjiaqi
		pPath = new char[100];
	}   //InfoProcessor.h

	//��������
	~InfoProcessor(void)
	{
		if(hTaskId != 0) 
		{

#ifdef VXWORKS 
			taskDelete(hTaskId);
#else
			TerminateThread(hTaskId, 0);
#endif

		}
		hTaskId = 0;
		m_iFunc = 0;
		m_NodeInfoMap.clear();
		m_CompInfoMap.clear();
		m_TopicInfoMap.clear();
		m_RecordInfoSeq.clear();

		if(m_hSemTopicWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemTopicWMutex);
#else
			CloseHandle(m_hSemTopicWMutex);
#endif
		}

		if(m_hSemCompWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemCompWMutex);
#else
			CloseHandle(m_hSemCompWMutex);
#endif
		}

		if(m_hSemNodeWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemNodeWMutex);
#else
			CloseHandle(m_hSemNodeWMutex);
#endif
		}

		if(m_hSemRecordInfoWMutex != NULL)
		{

#ifdef VXWORKS
			semDelete(m_hSemRecordInfoWMutex);
#else
			CloseHandle(m_hSemRecordInfoWMutex);
#endif
		}
		if(m_pSubManager != NULL)
		{
			delete m_pSubManager;
			m_pSubManager = NULL;
		}
		m_pProcessor = NULL;
		//fengjiaqi
		delete[] pPath;
	}    //InfoProcessor.h
	//��ʼ�������ź���
	_RETURNCODE_T InitialMonitorSemaphore();   //InfoProcessor.h
	_RETURNCODE_T InitialRecordSemaphore();   //InfoProcessor.h

	//��ʼ��������
	static _RETURNCODE_T InitializeMonitor(InfoProcessor* pProcessor, list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	static _RETURNCODE_T InitializeRecord(InfoProcessor* pProcessor, list<unsigned long> 	DomainIDList,list<string> TopicName);  //InfoProcessor.h
	//��ʼ��������
	_RETURNCODE_T InitializeMonitor(list<unsigned long> 	DomainIDList);   //InfoProcessor.h
	_RETURNCODE_T InitializeRecord(list<unsigned long> 	DomainIDList, list<string> TopicName);   //InfoProcessor.h

};

#endif
