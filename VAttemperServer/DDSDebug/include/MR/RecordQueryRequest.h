/************************************************************
** �ļ�����RecordQueryRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-25
** �޸��ˣ���
** ��  �ڣ���
** ��  ����RecordQueryRequestͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordQueryRequest_H
#define _RecordQueryRequest_H

#include <fstream>
#include <string>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::string;
using namespace std;

#include "MRBasicTypes.h"
#include "MRReturnCode.h"

class RecordQueryRequest
{
public:

#ifdef VXWORKS   
	SEM_ID m_hSemMutexDRSRecord;
	SEM_ID m_hSemMutexRecordContent;
#else
	HANDLE m_hSemMutexDRSRecord;
	HANDLE m_hSemMutexRecordContent;
#endif

	//���캯��
	RecordQueryRequest()
	{	//��ʼ�������ź���
#ifdef VXWORKS
		memset(&m_hSemMutexDRSRecord, 0, sizeof(SEM_ID));	
		m_hSemMutexDRSRecord = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
		memset(&m_hSemMutexRecordContent, 0, sizeof(SEM_ID));	
		m_hSemMutexRecordContent = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
#else
		m_hSemMutexDRSRecord = CreateMutex(NULL,FALSE,NULL);
		m_hSemMutexRecordContent = CreateMutex(NULL,FALSE,NULL);
#endif

	}                   //RecordQueryRequest.h
	//��������
	~RecordQueryRequest()
	{
#ifdef VXWORKS
		semDelete(m_hSemMutexDRSRecord);
		semDelete(m_hSemMutexRecordContent);
#else
		CloseHandle(m_hSemMutexDRSRecord);
		CloseHandle(m_hSemMutexRecordContent);
#endif

	}                //RecordQueryRequest.h

	//  ��ѯ����ֲ��MFC��

	//������ݿ�
	_RETURNCODE_T RecordEmpty();              //RecordQueryRequest.h

};

#endif
