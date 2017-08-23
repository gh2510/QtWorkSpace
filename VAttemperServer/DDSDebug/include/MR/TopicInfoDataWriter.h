/************************************************************
** 文件名：TopicInfoDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：TopicInfoDataWriter头文件
** 版  本：Version 0.1
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
	//构造函数
	TopicInfoDataWriter(Topic* pTopic,
						const _DATA_WRITER_QOS *pQos,
						DataWriterListener* pListener,
						_STATUS_MASK Mask,
						Publisher* pPublisher,
						unsigned long ulCacheLength) :
							DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }  //TopicInfoDataWriter.h

	//析构函数
	~TopicInfoDataWriter() { }  //TopicInfoDataWriter.h

	//返回type_id
	static int type_id() 
	{
		return 0; 
	}  //TopicInfoDataWriter.h

	//narrow_helper
	void* narrow_helper(long lType_const);  //TopicInfoDataWriter.h

	//将data写入缓冲区
	_RETURNCODE_T Write(_TOPIC_INFO Data);  //TopicInfoDataWriter.h

	//将DataWriter转化为TopicInfoDataWriter类型
	static TopicInfoDataWriter* Narrow(DataWriter* pDataWriter);  //TopicInfoDataWriter.h


	//重写内置writer的writeFinished函数，不删除HistoryCache中任何记录
	virtual _RETURNCODE_T WriteFinished(_SEQUENCE_NUMBER_T SeqNum);  //TopicInfoDataWriter.h

};

#endif
