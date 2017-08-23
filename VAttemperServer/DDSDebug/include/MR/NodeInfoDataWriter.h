/************************************************************
** 文件名：NodeInfoDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：NodeInfoDataWriter头文件
** 版  本：Version 0.1
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
	//构造函数
	NodeInfoDataWriter(Topic* pTopic,
									const _DATA_WRITER_QOS *pQos,
									DataWriterListener* pListener,
									_STATUS_MASK Mask,
									Publisher* pPublisher,
									unsigned long ulCacheLength) :
							DataWriter(pTopic, pQos, pListener, Mask, pPublisher, ulCacheLength) { }              //NodeInfoDataWriter.h

	//析构函数
	~NodeInfoDataWriter() { }                //NodeInfoDataWriter.h         

	//返回type_id
	static int type_id() 
	{ 
		return 0; 
	}            //NodeInfoDataWriter.h

	//narrow_helper
	void* narrow_helper(long lType_const);         //NodeInfoDataWriter.h

	//将data写入缓冲区
	_RETURNCODE_T Write(_NODE_INFO Data);             //NodeInfoDataWriter.h

	//将DataWriter转化为NodeInfoDataWriter类型
	static NodeInfoDataWriter* Narrow(DataWriter* pDataWriter);               //NodeInfoDataWriter.h

};

#endif
