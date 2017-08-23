/************************************************************
** �ļ�����recordinfosendlistdrlistener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����recordinfosendlistdrlistenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordInfoSendListDRListener_H
#define _RecordInfoSendListDRListener_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class RecordInfoSendListDRListener:public DataReaderListener
{
public:
	//fengjiaqi
	RecordInfoSendListDRListener(InfoProcessor *pProcessor, DomainParticipant* pDDSParticipant);         //recordinfosendlistdrlistener.h
	~RecordInfoSendListDRListener();          //recordinfosendlistdrlistener.h  
	//���ݵ���֪ͨ
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);              //recordinfosendlistdrlistener.h
	//���β������
	_RETURNCODE_T RemainingRecordStore(DataReader* pDataReader);         //recordinfosendlistdrlistener.h
	//fengjiaqi
	//��ȡ��DDSParticipant״̬�����/��¼
	int GetStatus();                    //recordinfosendlistdrlistener.h
	//fengjiaqi
	//�浽����ش洢�ṹ��
	_RETURNCODE_T StoreMonitorDataRI(_RECORD_INFO_SENDLIST InfoRecvs);            //recordinfosendlistdrlistener.h
	//fengjiaqi
	//�洢����¼�洢�ṹ��
	_RETURNCODE_T StoreRecordDataRI(_RECORD_INFO_SENDLIST InfoRecvs);            //recordinfosendlistdrlistener.h

private:
	//������ָ��
	InfoProcessor *m_pProcessor;
	//��¼����������
	_RECORD_INFO_LIST m_RecordSeq;
	//fengjiaqi
	//������DomainParticipant
	DomainParticipant* m_pDDSParticipant;

#ifdef VXWORKS   
	//������
	SEM_ID m_hSemRecord;
#else
	//������
	HANDLE m_hSemRecord;
#endif

};

#endif

