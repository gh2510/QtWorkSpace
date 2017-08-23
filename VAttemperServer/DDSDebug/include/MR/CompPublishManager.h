/************************************************************
** �ļ�����CompPublishManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-10-05
** ��  ����CompPublishManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/


#ifndef CompsPublishManager_hh
#define CompsPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class CompInfoDataWriter;
class MonitorRecordAgent;

class CompPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;   
	//����������Ϣ��DataWriter
	CompInfoDataWriter *m_pDataWriter;   
	//����
	Topic *m_pTopic;  
	//�����ָ��
	MonitorRecordAgent *m_pAgent;   

public:
	//���캯��
	CompPublishManager(MonitorRecordAgent *pAgent);  //CompPublishManager.h
	//��������
	~CompPublishManager();  //CompPublishManager.h

	//����CompInfoDataWriter
	_RETURNCODE_T CreateCompInfoDW(void);  //CompPublishManager.h
	//��������
	_RETURNCODE_T CreateCompInfoTopic(void);  //CompPublishManager.h
	//����������Ϣ
	_RETURNCODE_T SendCompInfo(_COMP_INFO* pData);  //CompPublishManager.h
	//ɾ������
	_RETURNCODE_T DeleteCompInfoTopic(void);  //CompPublishManager.h
	//ɾ��CompInfoDataWriter
	_RETURNCODE_T  DeleteCompInfoDW(void);  //CompPublishManager.h
};

#endif
