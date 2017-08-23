/************************************************************
** 文件名：recordinfosendlistdrlistener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：recordinfosendlistdrlistener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _RecordInfoSendListDRListener_H
#define _RecordInfoSendListDRListener_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class RecordInfoSendListDRListener:public DataReaderListener
{
public:
	//fengjiaqi
	RecordInfoSendListDRListener(InfoProcessor *pProcessor, DomainParticipant* pDDSParticipant);         //recordinfosendlistdrlistener.h
	~RecordInfoSendListDRListener();          //recordinfosendlistdrlistener.h  
	//数据到达通知
	_RETURNCODE_T On_Data_Available(DataReader* pDataReader);              //recordinfosendlistdrlistener.h
	//存放尾部数据
	_RETURNCODE_T RemainingRecordStore(DataReader* pDataReader);         //recordinfosendlistdrlistener.h
	//fengjiaqi
	//获取本DDSParticipant状态：监控/记录
	int GetStatus();                    //recordinfosendlistdrlistener.h
	//fengjiaqi
	//存到到监控存储结构中
	_RETURNCODE_T StoreMonitorDataRI(_RECORD_INFO_SENDLIST InfoRecvs);            //recordinfosendlistdrlistener.h
	//fengjiaqi
	//存储到记录存储结构中
	_RETURNCODE_T StoreRecordDataRI(_RECORD_INFO_SENDLIST InfoRecvs);            //recordinfosendlistdrlistener.h

private:
	//处理器指针
	InfoProcessor *m_pProcessor;
	//记录的数据序列
	_RECORD_INFO_LIST m_RecordSeq;
	//fengjiaqi
	//所属的DomainParticipant
	DomainParticipant* m_pDDSParticipant;

#ifdef VXWORKS   
	//互斥锁
	SEM_ID m_hSemRecord;
#else
	//互斥锁
	HANDLE m_hSemRecord;
#endif

};

#endif

