/************************************************************
** 文件名：RecordInfoSendListDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：RecordInfoSendListDataWriter头文件
** 版  本：Version 0.1
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
	//构造函数
	RecordInfoSendListDataWriter(Topic* pTopic,
										const _DATA_WRITER_QOS* pQos,
										DataWriterListener* pListener,
										_STATUS_MASK Mask,
										Publisher* pPublisher,
										unsigned long ulCacheLength) :
									DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }      //RecordInfoSendListDataWriter.h

	//析构函数
	~RecordInfoSendListDataWriter() { }            //RecordInfoSendListDataWriter.h

	//返回type_id
	static int type_id()
	{
		return 0; 
	}                        //RecordInfoSendListDataWriter.h

	//用于判断narrow操作是否成功
	void* narrow_helper(long lType_const);          //RecordInfoSendListDataWriter.h

	//写数据
	_RETURNCODE_T Write(_RECORD_INFO_SENDLIST Data);       //RecordInfoSendListDataWriter.h

	//将发布端转为数据记录发布端
	static RecordInfoSendListDataWriter* Narrow(DataWriter* pDataWriter) ;         //RecordInfoSendListDataWriter.h

};

#endif
