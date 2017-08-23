/************************************************************
** 文件名：RecordInfoSendListDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：RecordInfoSendListDataReader头文件
** 版  本：Version 0.1
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
	//数据记录订阅端构造函数
	RecordInfoSendListDataReader(TopicDescription* pTopic,
													const _DATA_READER_QOS *pQos,
													DataReaderListener* pListener,
													_STATUS_MASK Mask,
													Subscriber* pSubscriber,
													unsigned long ulCacheLength) :	DataReader(pTopic, pQos, pListener, Mask, pSubscriber, ulCacheLength) { }     //RecordInfoSendListDataReader.h

	//数据记录订阅端析构函数
	~RecordInfoSendListDataReader() {}         //RecordInfoSendListDataReader.h

	//类的地址
	static int type_id()
	{ 
		return 0; 
	}                        //RecordInfoSendListDataReader.h

	//用于判断narrow操作是否成功
	void* narrow_helper(long lType_const) ;            //RecordInfoSendListDataReader.h

	//将data读入缓冲区
	//_RETURNCODE_T read(_RECORD_INFO_SENDLIST_SEQ& receivedDataSeq, long maxSamples);

	//读取下一个数据
	_RETURNCODE_T Read_Next_Sample(_RECORD_INFO_SENDLIST* pReceivedData) ;           //RecordInfoSendListDataReader.h

	//将订阅端转为数据记录订阅端
	static RecordInfoSendListDataReader* Narrow(DataReader* pDataReader) ;          //RecordInfoSendListDataReader.h
};

#endif
