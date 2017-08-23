//������
/************************************************************
** �ļ�����MassDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2013-07-24
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MassDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREQUEST_H_INCLUDED_
#define _DDS_MASSDATAREQUEST_H_INCLUDED_
#include "BasicTypes.h"
#include "DDS/DataWriter.h"

class MassDataRequest
{
public:
    //���캯��
    MassDataRequest(char *pData, unsigned long Datalen, unsigned long DataNum, DataWriter *pRelatedDataWriter, _TIME_T Deadline);

    //��������
	virtual ~MassDataRequest(){};

	bool Execute();

	_TIME_T m_NextSendTime;
	_TIME_T m_LastSendTime;
private:
	char *m_pData;
	unsigned long m_Datalen;
	unsigned long m_DataNum;
	DataWriter *m_pRelatedDataWriter;
	unsigned long m_FragNum;
	char *m_pPosition;
	_TIME_T m_Deadline;
};

#endif
