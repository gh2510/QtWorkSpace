/************************************************************
** �ļ�����TopicInfoDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����TopicInfoDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef TopicInfoDataWriter_hh
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

class TopicInfoDataWriter : public DataWriter 
{
public:
	//���캯��
	TopicInfoDataWriter(Topic* pTopic,
						const _DATA_WRITER_QOS *pQos,
						DataWriterListener* pListener,
						_STATUS_MASK Mask,
						Publisher* pPublisher,
						unsigned long ulCacheLength) :
							DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }  //TopicInfoDataWriter.h

	//��������
	~TopicInfoDataWriter() { }  //TopicInfoDataWriter.h

	//����type_id
	static int type_id() 
	{
		return 0; 
	}  //TopicInfoDataWriter.h

	//narrow_helper
	void* narrow_helper(long lType_const);  //TopicInfoDataWriter.h

	//��dataд�뻺����
	_RETURNCODE_T Write(_TOPIC_INFO Data);  //TopicInfoDataWriter.h

	//��DataWriterת��ΪTopicInfoDataWriter����
	static TopicInfoDataWriter* Narrow(DataWriter* pDataWriter);  //TopicInfoDataWriter.h


	//��д����writer��writeFinished��������ɾ��HistoryCache���κμ�¼
	virtual _RETURNCODE_T WriteFinished(_SEQUENCE_NUMBER_T SeqNum);  //TopicInfoDataWriter.h

};

#endif
