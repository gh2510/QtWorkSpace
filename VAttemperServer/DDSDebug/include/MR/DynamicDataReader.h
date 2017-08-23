/************************************************************
** �ļ�����DynamicDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DynamicDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DYNAMICDATAREADER_H_
#define _DYNAMICDATAREADER_H_
#include <string>
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"

using std::string;

typedef list<_RECORD_CONTENT> _DYNAMIC_SEQ;

class DynamicDataReader : public DataReader 
{
public:
	//��̬���Ķ˹��캯��
	DynamicDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long pCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, pCacheLength) 
	{ 
										//cout<<"DynamicDataReader "<<pTopic->get_name()<<endl;
	}         //DynamicDataReader.h

	//���ݼ�¼���Ķ���������
	~DynamicDataReader() {}   //DynamicDataReader.h

	//��ĵ�ַ
	static int type_id()
	{
		return 0; 
	}   //DynamicDataReader.h

	//�����ж�narrow�����Ƿ�ɹ�
	void* narrow_helper(long lType_const) ;   //DynamicDataReader.h

	//��data���뻺����
	//_RETURNCODE_T read(_DYNAMIC_SEQ& receivedDataSeq, long maxSamples);

	//��ȡ��һ������
	_RETURNCODE_T Read_Next_Sample(char* pReceivedData) ;    //DynamicDataReader.h

	//�����Ķ�תΪ���ݼ�¼���Ķ�
	static DynamicDataReader* Narrow(DataReader* pDataReader) ;   //DynamicDataReader.h
};

#endif
