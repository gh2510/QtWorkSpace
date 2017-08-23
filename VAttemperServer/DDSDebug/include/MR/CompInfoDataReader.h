/************************************************************
** 文件名：CompInfoDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011/04/26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011/8/24
** 描  述：CompInfoDataReader头文件
** 版  本：Version 0.1
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
	//构造函数
	CompInfoDataReader(TopicDescription* pTopic,
									const _DATA_READER_QOS *pQos,
									DataReaderListener* pListener,
									_STATUS_MASK Mask,
									Subscriber* pSubscriber,
									unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { } //CompInfoDataReader.h

	//析构函数
	~CompInfoDataReader() {}  //CompInfoDataReader.h

	//返回type_id
	static int type_id() 
	{ 
		return 0; 
	}  //CompInfoDataReader.h

	//narrow_helper
	void* narrow_helper(long lType_const);   //CompInfoDataReader.h

	//将数据读入缓冲区
	//_RETURNCODE_T read(_COMP_INFO_SEQ& receivedDataSeq, long maxSamples);

	//读下一个数据
	_RETURNCODE_T Read_Next_Sample(_COMP_INFO& ReceivedData);  //CompInfoDataReader.h

	//将dataReader转化为CompInfoDataReader类型
	static CompInfoDataReader* Narrow(DataReader* pDataReader);  //CompInfoDataReader.h

};

#endif
