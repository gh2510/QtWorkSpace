//大数据
/************************************************************
** 文件名：MassDataListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<xusen.seu.edu.cn>
** 日  期：2013-07-25
** 修改人：无
** 日  期：无
** 描  述：MassDataListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATA_LISTENER_H_INCLUDED_
#define _DDS_MASSDATA_LISTENER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DataReaderListener.h"

class DataReader;
class MassDataReader;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE) || defined(KYLIN)
class MassDataListener : public DataReaderListener
{
#else
class DDS_DLL MassDataListener : public DataReaderListener
{
#endif
public:
    MassDataListener() {};
    virtual ~MassDataListener() {};
    _RETURNCODE_T On_Data_Available(DataReader* pMassDataReader);
	virtual _RETURNCODE_T On_Mass_Data_Available(MassDataReader* pMassDataReader){ return RETURNCODE_OK; }
};

#endif