/************************************************************
** 文件名：CompInfoDRListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-10-05
** 描  述：CompInfoDRListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _COMPINFODRLISTENER_H
#define _COMPINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class CompInfoDRListener:public DataReaderListener
{
private:
	//处理器指针
	InfoProcessor *m_pProcessor;
public:
	//构造函数
	CompInfoDRListener(InfoProcessor *pProcessor);   //CompInfoDRListener.h
	//析构函数
	~CompInfoDRListener();   //CompInfoDRListener.h
	//数据到达时，处理数据的函数
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);   //CompInfoDRListener.h
};

#endif

