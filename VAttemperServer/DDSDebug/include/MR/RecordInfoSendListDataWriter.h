/************************************************************
** �ļ�����RecordInfoSendListDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����RecordInfoSendListDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef RecordInfoSendListDataWriter_hh
#define RecordInfoSendListDataWriter_hh
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

class RecordInfoSendListDataWriter : public DataWriter 
{
public:
	//���캯��
	RecordInfoSendListDataWriter(Topic* pTopic,
										const _DATA_WRITER_QOS* pQos,
										DataWriterListener* pListener,
										_STATUS_MASK Mask,
										Publisher* pPublisher,
										unsigned long ulCacheLength) :
									DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }      //RecordInfoSendListDataWriter.h

	//��������
	~RecordInfoSendListDataWriter() { }            //RecordInfoSendListDataWriter.h

	//����type_id
	static int type_id()
	{
		return 0; 
	}                        //RecordInfoSendListDataWriter.h

	//�����ж�narrow�����Ƿ�ɹ�
	void* narrow_helper(long lType_const);          //RecordInfoSendListDataWriter.h

	//д����
	_RETURNCODE_T Write(_RECORD_INFO_SENDLIST Data);       //RecordInfoSendListDataWriter.h

	//��������תΪ���ݼ�¼������
	static RecordInfoSendListDataWriter* Narrow(DataWriter* pDataWriter) ;         //RecordInfoSendListDataWriter.h

};

#endif
