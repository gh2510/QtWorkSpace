/************************************************************
** �ļ�����NodePublishManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����NodePublishManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef NodePublishManager_hh
#define  NodePublishManager_hh

#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"

class DomainParticipant;
class NodeInfoDataWriter;
class MonitorRecordAgent;

class NodePublishManager
{
private:
	//DomainParticipant
	DomainParticipant *m_pDDSParticipant;
	//����������Ϣ��DataWriter
	NodeInfoDataWriter *m_pDataWriter;
	//����
	Topic *m_pTopic;
	//�����ָ��
	MonitorRecordAgent *m_pAgent;

public:
	//���캯��
	NodePublishManager(MonitorRecordAgent *pAgent);                //NodePublishManager.h
	//��������
	~NodePublishManager();                    //NodePublishManager.h

	//����NodeInfoDataWriter
	_RETURNCODE_T CreateNodeInfoDW(void);                //NodePublishManager.h
	//��������
	_RETURNCODE_T CreateNodeInfoTopic(void);              //NodePublishManager.h
	//����������Ϣ
	_RETURNCODE_T SendNodeInfo(_NODE_INFO* pData);          //NodePublishManager.h
	//ɾ������
	_RETURNCODE_T DeleteNodeInfoTopic(void);            //NodePublishManager.h
	//ɾ��NodeInfoDataWriter
	_RETURNCODE_T  DeleteNodeInfoDW(void);               //NodePublishManager.h

};

#endif
