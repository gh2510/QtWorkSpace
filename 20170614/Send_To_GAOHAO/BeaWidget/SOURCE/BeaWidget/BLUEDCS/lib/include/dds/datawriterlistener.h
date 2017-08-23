/************************************************************
** 文件名：DataWriterListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-20
** 修改人：无
** 日  期：无
** 描  述：DataWriterListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAWRITERLISTENER_H_INCLUDED_
#define _DDS_DATAWRITERLISTENER_H_INCLUDED_
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DDSListener.h"

class DataReader;
class DataWriter;

class DataWriterListener : DDSListener 
{
public:
    DataWriterListener() {}
    virtual ~DataWriterListener() {}
    //成功则返回RETURNCODE_OK
    virtual _RETURNCODE_T On_Offered_Deadline_Missed(DataWriter* pDataWriter, const _OFFERED_DEADLINE_MISSED_STATUS& Status) 
    {	
        return RETURNCODE_OK;    
    }
};

#endif
