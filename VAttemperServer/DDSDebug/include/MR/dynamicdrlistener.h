/************************************************************
** 文件名：dynamicdrlistener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：无
** 日  期：无
** 描  述：dynamicdrlistener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DynamicDRListener_H
#define _DynamicDRListener_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class DynamicDRListener:public DataReaderListener
{
private:
	//处理器指针
	InfoProcessor *m_pProcessor;

#ifdef VXWORKS 
	//互斥锁
	SEM_ID m_hSemRecord;
#else
	//互斥锁
	HANDLE m_hSemRecord;
#endif

	char* m_pTopicName;
	//unsigned long m_ipAddress;
	list<_RECORD_CONTENT> m_RecordContentList;
public:
	DynamicDRListener(InfoProcessor* pProcessor, char* pTopicName, unsigned long ulIPAddress);   //dynamicdrlistener.h
	~DynamicDRListener();  //dynamicdrlistener.h
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);   //dynamicdrlistener.h
};

#endif
