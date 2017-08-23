/************************************************************
** �ļ�����RecordInfoSendListDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����RecordInfoSendListDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordInfoSendListDATAREADER_H_
#define _RecordInfoSendListDATAREADER_H_

#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Cdr.h"
#include <string>
using std::string;

typedef list<_RECORD_INFO_SENDLIST> _RECORD_INFO_SENDLIST_SEQ;
class RecordInfoSendListDataReader : public DataReader 
{
public:
	//���ݼ�¼���Ķ˹��캯��
	RecordInfoSendListDataReader(TopicDescription* pTopic,
													const _DATA_READER_QOS *pQos,
													DataReaderListener* pListener,
													_STATUS_MASK Mask,
													Subscriber* pSubscriber,
													unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }     //RecordInfoSendListDataReader.h

	//���ݼ�¼���Ķ���������
	~RecordInfoSendListDataReader() {}         //RecordInfoSendListDataReader.h

	//��ĵ�ַ
	static int type_id()
	{ 
		return 0; 
	}                        //RecordInfoSendListDataReader.h

	//�����ж�narrow�����Ƿ�ɹ�
	void* narrow_helper(long lType_const) ;            //RecordInfoSendListDataReader.h

	//��data���뻺����
	//_RETURNCODE_T read(_RECORD_INFO_SENDLIST_SEQ& receivedDataSeq, long maxSamples);

	//��ȡ��һ������
	_RETURNCODE_T Read_Next_Sample(_RECORD_INFO_SENDLIST* pReceivedData) ;           //RecordInfoSendListDataReader.h

	//�����Ķ�תΪ���ݼ�¼���Ķ�
	static RecordInfoSendListDataReader* Narrow(DataReader* pDataReader) ;          //RecordInfoSendListDataReader.h
};

#endif
