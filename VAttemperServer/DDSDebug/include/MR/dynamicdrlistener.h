/************************************************************
** �ļ�����dynamicdrlistener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����dynamicdrlistenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DynamicDRListener_H
#define _DynamicDRListener_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class DynamicDRListener:public DataReaderListener
{
private:
	//������ָ��
	InfoProcessor *m_pProcessor;

#ifdef VXWORKS 
	//������
	SEM_ID m_hSemRecord;
#else
	//������
	HANDLE m_hSemRecord;
#endif

	char* m_pTopicName;
	//unsigned long m_ipAddress;
	list<_RECORD_CONTENT> m_RecordContentList;
public:
	DynamicDRListener(InfoProcessor* pProcessor, char* pTopicName, unsigned long ulIPAddress);   //dynamicdrlistener.h
	~DynamicDRListener();  //dynamicdrlistener.h
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);   //dynamicdrlistener.h
};

#endif
