/************************************************************
** 文件名：topicinfodrlistener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：topicinfodrlistener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _TOPICINFODRLISTENER_H
#define _TOPICINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class TopicInfoDRListener:public DataReaderListener
{
private:
	//处理器指针
	InfoProcessor *m_pProcessor;
	//记录的数据序列
	_RECORD_INFO_LIST m_RecordSeq;


#ifdef VXWORKS   
	SEM_ID m_hSemRecord;
#else
	HANDLE m_hSemRecord;
#endif

	//所属的DomainParticipant
	DomainParticipant* m_pDDSParticipant;

public:
	//构造函数
	TopicInfoDRListener(InfoProcessor *pProcessor, DomainParticipant* pDDSParticipant);  //topicinfodrlistener.h
	//析构函数
	~TopicInfoDRListener();  //topicinfodrlistener.h
	//接收到数据时，数据的处理函数
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);  //topicinfodrlistener.h
	//存放尾部数据
	_RETURNCODE_T RemainingRecordStore(DataReader* pDataReader);  //topicinfodrlistener.h

	//获取本DDSParticipant状态：监控/记录
	int GetStatus();  //topicinfodrlistener.h
	//存到到监控存储结构中
	_RETURNCODE_T StoreMonitorData(_TOPIC_INFO TopicInfo);  //topicinfodrlistener.h
	//存储到记录存储结构中
	_RETURNCODE_T StoreRecordData(_TOPIC_INFO TopicInfo);  //topicinfodrlistener.h

};

#endif
