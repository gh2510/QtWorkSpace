/************************************************************
** 文件名：DynamicDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：无
** 日  期：无
** 描  述：DynamicDataReader头文件
** 版  本：Version 0.1
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
	//动态订阅端构造函数
	DynamicDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long pCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, pCacheLength) 
	{ 
										//cout<<"DynamicDataReader "<<pTopic->get_name()<<endl;
	}         //DynamicDataReader.h

	//数据记录订阅端析构函数
	~DynamicDataReader() {}   //DynamicDataReader.h

	//类的地址
	static int type_id()
	{
		return 0; 
	}   //DynamicDataReader.h

	//用于判断narrow操作是否成功
	void* narrow_helper(long lType_const) ;   //DynamicDataReader.h

	//将data读入缓冲区
	//_RETURNCODE_T read(_DYNAMIC_SEQ& receivedDataSeq, long maxSamples);

	//读取下一个数据
	_RETURNCODE_T Read_Next_Sample(char* pReceivedData) ;    //DynamicDataReader.h

	//将订阅端转为数据记录订阅端
	static DynamicDataReader* Narrow(DataReader* pDataReader) ;   //DynamicDataReader.h
};

#endif
