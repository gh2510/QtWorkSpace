//大数据
/************************************************************
** 文件名：MassDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<xusen.seu.edu.cn>
** 日  期：2013-07-24
** 修改人：无
** 日  期：无
** 描  述：MassDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREQUEST_H_INCLUDED_
#define _DDS_MASSDATAREQUEST_H_INCLUDED_
#include "BasicTypes.h"
#include "dds/DataWriter.h"

class MassDataRequest
{
public:
    //构造函数
    MassDataRequest(char *pData, unsigned long Datalen, unsigned long DataNum, DataWriter *pRelatedDataWriter, _TIME_T Deadline);

    //析构函数
	virtual ~MassDataRequest(){};

	bool Execute();

	_TIME_T m_NextSendTime;
	_TIME_T m_LastSendTime;
private:
	char *m_pData;
	unsigned long m_Datalen;
	unsigned long m_DataNum;
	DataWriter *m_pRelatedDataWriter;
	unsigned long m_FragNum;
	char *m_pPosition;
	_TIME_T m_Deadline;
};

#endif
