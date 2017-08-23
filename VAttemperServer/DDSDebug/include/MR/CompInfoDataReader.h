/************************************************************
** �ļ�����CompInfoDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/04/26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/8/24
** ��  ����CompInfoDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _CompInfoDATAREADER_H_
#define _CompInfoDATAREADER_H_

#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Cdr.h"
#include <string>
using std::string;

typedef list<_COMP_INFO> _COMP_INFO_SEQ;

class CompInfoDataReader : public DataReader 
{
public:
	//���캯��
	CompInfoDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { } //CompInfoDataReader.h

	//��������
	~CompInfoDataReader() {}  //CompInfoDataReader.h

	//����type_id
	static int type_id() 
	{ 
		return 0; 
	}  //CompInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);   //CompInfoDataReader.h

	//�����ݶ��뻺����
	//_RETURNCODE_T read(_COMP_INFO_SEQ& receivedDataSeq, long maxSamples);

	//����һ������
	_RETURNCODE_T Read_Next_Sample(_COMP_INFO& ReceivedData);  //CompInfoDataReader.h

	//��dataReaderת��ΪCompInfoDataReader����
	static CompInfoDataReader* Narrow(DataReader* pDataReader);  //CompInfoDataReader.h

};

#endif
