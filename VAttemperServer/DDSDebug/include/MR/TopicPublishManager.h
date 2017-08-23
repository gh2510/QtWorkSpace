/************************************************************
** �ļ�����TopicPublishManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����TopicPublishManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef TopicPublishManager_hh
#define TopicPublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class TopicInfoDataWriter;
class MonitorRecordAgent;

class TopicPublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//����������Ϣ��DataWriter
	TopicInfoDataWriter *m_pDataWriter;
	//����
	Topic *m_pTopic;
	//�����ָ��
	MonitorRecordAgent *m_pAgent;

public:
	//���캯��
	TopicPublishManager(MonitorRecordAgent *pAgent);   //TopicPublishManager.h
	//��������
	~TopicPublishManager();  //TopicPublishManager.h

	//����TopicInfoDataWriter
	_RETURNCODE_T CreateTopicInfoDW(void);  //TopicPublishManager.h
	//��������
	_RETURNCODE_T CreateTopicInfoTopic(void);  //TopicPublishManager.h
	//����������Ϣ
	_RETURNCODE_T SendTopicInfo(_TOPIC_INFO* pData);  //TopicPublishManager.h
	//ɾ������
	_RETURNCODE_T DeleteTopicInfoTopic(void);  //TopicPublishManager.h
	//ɾ��TopicInfoDataWriter
	_RETURNCODE_T  DeleteTopicInfoDW(void);  //TopicPublishManager.h

};

#endif
