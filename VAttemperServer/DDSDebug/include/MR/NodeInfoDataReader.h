/************************************************************
** 文件名：NodeInfoDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：NodeInfoDataReader头文件
** 版  本：Version 0.1
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
	//构造函数
	NodeInfoDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }      //NodeInfoDataReader.h

	//析构函数
	~NodeInfoDataReader() {}               //NodeInfoDataReader.h

	//返回type_id
	static int type_id() 
	{ 
		return 0; 
	}             //NodeInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);                //NodeInfoDataReader.h

	//将数据读入缓冲区
	//_RETURNCODE_T read(NodeInfoSeq& receivedDataSeq, long maxSamples);

	//读下一个数据
	_RETURNCODE_T Read_Next_Sample(_NODE_INFO& ReceivedData);                 //NodeInfoDataReader.h

	//将dataReader转化为NodeInfoDataReader类型
	static NodeInfoDataReader* narrow(DataReader* pDataReader);              //NodeInfoDataReader.h

};

#endif
