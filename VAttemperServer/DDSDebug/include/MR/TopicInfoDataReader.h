/************************************************************
** 文件名：TopicInfoDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：TopicInfoDataReader头文件
** 版  本：Version 0.1
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
	//构造函数
	TopicInfoDataReader(TopicDescription* pTopic,
						const _DATA_READER_QOS *pQos,
						DataReaderListener* pListener,
						_STATUS_MASK Mask,
						Subscriber* pSubscriber,
						unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }   //TopicInfoDataReader.h

	//析构函数
	~TopicInfoDataReader() {}   //TopicInfoDataReader.h

	//返回type_id
	static int type_id() 
	{
		return 0; 
	}   //TopicInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);   //TopicInfoDataReader.h

	//将data读入缓冲区
	//_RETURNCODE_T read(TopicInfoSeq& receivedDataSeq, long maxSamples);

	//读下一个数据
	_RETURNCODE_T Read_Next_Sample(_TOPIC_INFO& ReceivedData);  //TopicInfoDataReader.h

	//将dataReader转化为TopicInfoDataReader类型
	static TopicInfoDataReader* Narrow(DataReader* pDataReader);  //TopicInfoDataReader.h

};

#endif
