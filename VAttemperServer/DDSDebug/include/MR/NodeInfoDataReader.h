/************************************************************
** �ļ�����NodeInfoDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����NodeInfoDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _NodeInfoDATAREADER_H_
#define _NodeInfoDATAREADER_H_

#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Cdr.h"
#include <string>
using std::string;

typedef list<_NODE_INFO> NodeInfoSeq;

class NodeInfoDataReader : public DataReader 
{
public:
	//���캯��
	NodeInfoDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }      //NodeInfoDataReader.h

	//��������
	~NodeInfoDataReader() {}               //NodeInfoDataReader.h

	//����type_id
	static int type_id() 
	{ 
		return 0; 
	}             //NodeInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);                //NodeInfoDataReader.h

	//�����ݶ��뻺����
	//_RETURNCODE_T read(NodeInfoSeq& receivedDataSeq, long maxSamples);

	//����һ������
	_RETURNCODE_T Read_Next_Sample(_NODE_INFO& ReceivedData);                 //NodeInfoDataReader.h

	//��dataReaderת��ΪNodeInfoDataReader����
	static NodeInfoDataReader* narrow(DataReader* pDataReader);              //NodeInfoDataReader.h

};

#endif
