/************************************************************
** �ļ�����CompInfoDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/04/26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/8/24
** ��  ����CompInfoDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef CompInfoDataWriter_hh
#define CompInfoDataWriter_hh
#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/DomainParticipant.h"
#include "dds/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/Topic.h"

#include <string>

class Publisher;
class Topic;
class DataWriterListener;

class CompInfoDataWriter : public DataWriter 
{
public:
	//���캯��
	CompInfoDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) :
								DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }   //CompInfoDataWriter.h

	//��������
	~CompInfoDataWriter() { }   //CompInfoDataWriter.h

	//����type_id
	static int type_id() { return 0; } //CompInfoDataWriter.h

	//narrow_helper
	void* narrow_helper(long ulType_const);  //CompInfoDataWriter.h

	//��dataд�뻺����
	_RETURNCODE_T Write(_COMP_INFO Data);  //CompInfoDataWriter.h

	//��dataWriterת��ΪCompInfoDataWriter����
	static CompInfoDataWriter* Narrow(DataWriter* pDataWriter);   //CompInfoDataWriter.h

};

#endif
