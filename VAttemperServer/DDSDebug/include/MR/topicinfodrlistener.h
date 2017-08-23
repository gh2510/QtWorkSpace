/************************************************************
** �ļ�����topicinfodrlistener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����topicinfodrlistenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _TOPICINFODRLISTENER_H
#define _TOPICINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class TopicInfoDRListener:public DataReaderListener
{
private:
	//������ָ��
	InfoProcessor *m_pProcessor;
	//��¼����������
	_RECORD_INFO_LIST m_RecordSeq;


#ifdef VXWORKS   
	SEM_ID m_hSemRecord;
#else
	HANDLE m_hSemRecord;
#endif

	//������DomainParticipant
	DomainParticipant* m_pDDSParticipant;

public:
	//���캯��
	TopicInfoDRListener(InfoProcessor *pProcessor, DomainParticipant* pDDSParticipant);  //topicinfodrlistener.h
	//��������
	~TopicInfoDRListener();  //topicinfodrlistener.h
	//���յ�����ʱ�����ݵĴ�����
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);  //topicinfodrlistener.h
	//���β������
	_RETURNCODE_T RemainingRecordStore(DataReader* pDataReader);  //topicinfodrlistener.h

	//��ȡ��DDSParticipant״̬�����/��¼
	int GetStatus();  //topicinfodrlistener.h
	//�浽����ش洢�ṹ��
	_RETURNCODE_T StoreMonitorData(_TOPIC_INFO TopicInfo);  //topicinfodrlistener.h
	//�洢����¼�洢�ṹ��
	_RETURNCODE_T StoreRecordData(_TOPIC_INFO TopicInfo);  //topicinfodrlistener.h

};

#endif
