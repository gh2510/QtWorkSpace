/************************************************************
** 文件名：NodeInfoDRListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-27
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-24
** 描  述：NodeInfoDRListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _NODEINFODRLISTENER_H
#define _NODEINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class NodeInfoDRListener:public DataReaderListener
{
private:
	//处理器指针
	InfoProcessor *m_pProcessor;
public:
	//构造函数
	NodeInfoDRListener(InfoProcessor *pProcessor);                 //NodeInfoDRListener.h
	//析构函数
	~NodeInfoDRListener();                        //NodeInfoDRListener.h
	//数据到达时，处理数据的函数
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);             //NodeInfoDRListener.h
};

#endif
