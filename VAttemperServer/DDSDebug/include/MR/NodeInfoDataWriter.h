/************************************************************
** �ļ�����NodeInfoDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����NodeInfoDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef NodeInfoDataWriter_hh
#define NodeInfoDataWriter_hh
#include"MRBasicTypes.h"
#include "MRReturnCode.h"
#include "dds/Cdr.h"

#include "dds/DomainParticipant.h"
#include "dds/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/Topic.h"

#include <string>
class Publisher;
class Topic;
class DataWriterListener;

class NodeInfoDataWriter : public DataWriter 
{
public:
	//���캯��
	NodeInfoDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) :
							DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }              //NodeInfoDataWriter.h

	//��������
	~NodeInfoDataWriter() { }                //NodeInfoDataWriter.h         

	//����type_id
	static int type_id() 
	{ 
		return 0; 
	}            //NodeInfoDataWriter.h

	//narrow_helper
	void* narrow_helper(long lType_const);         //NodeInfoDataWriter.h

	//��dataд�뻺����
	_RETURNCODE_T Write(_NODE_INFO Data);             //NodeInfoDataWriter.h

	//��DataWriterת��ΪNodeInfoDataWriter����
	static NodeInfoDataWriter* Narrow(DataWriter* pDataWriter);               //NodeInfoDataWriter.h

};

#endif
