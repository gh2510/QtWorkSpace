/************************************************************
** �ļ�����DurabilityDataReaderListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-04-05
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DurabilityDataReaderListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DURABILITYDATAREADERLISTENER_H
#define _DURABILITYDATAREADERLISTENER_H

#include "dds/DataReaderListener.h"
class DataBaseManager;
class DurabilityDataReaderListener : public DataReaderListener
{
private:
	//���ݿ����ָ��
	DataBaseManager *m_pManager;

#ifdef VXWORKS 
	//������
	SEM_ID m_hSemMutex;
#else
	//������
	HANDLE m_hSemMutex;
#endif

	char* m_pTopicName;
	char* m_pTypeName;
	//unsigned long m_ipAddress;
//	list<RecordContent> m_recordContentList;
public:
	DurabilityDataReaderListener(DataBaseManager* pManager, char* pTopicName, char* pTypeName);
	~DurabilityDataReaderListener();
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);
};

#endif
