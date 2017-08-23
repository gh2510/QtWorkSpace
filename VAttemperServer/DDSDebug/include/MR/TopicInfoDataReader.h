/************************************************************
** �ļ�����TopicInfoDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����TopicInfoDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _TopicInfoDATAREADER_H_
#define _TopicInfoDATAREADER_H_

#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Cdr.h"
#include <string>
using std::string;

typedef list<_TOPIC_INFO> TopicInfoSeq;

class TopicInfoDataReader : public DataReader 
{
public:
	//���캯��
	TopicInfoDataReader(TopicDescription* pTopic,
						const _DATA_READER_QOS *pQos,
						DataReaderListener* pListener,
						_STATUS_MASK Mask,
						Subscriber* pSubscriber,
						unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }   //TopicInfoDataReader.h

	//��������
	~TopicInfoDataReader() {}   //TopicInfoDataReader.h

	//����type_id
	static int type_id() 
	{
		return 0; 
	}   //TopicInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);   //TopicInfoDataReader.h

	//��data���뻺����
	//_RETURNCODE_T read(TopicInfoSeq& receivedDataSeq, long maxSamples);

	//����һ������
	_RETURNCODE_T Read_Next_Sample(_TOPIC_INFO& ReceivedData);  //TopicInfoDataReader.h

	//��dataReaderת��ΪTopicInfoDataReader����
	static TopicInfoDataReader* Narrow(DataReader* pDataReader);  //TopicInfoDataReader.h

};

#endif
