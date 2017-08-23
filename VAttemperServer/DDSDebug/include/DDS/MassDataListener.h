//������
/************************************************************
** �ļ�����MassDataListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2013-07-25
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MassDataListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATA_LISTENER_H_INCLUDED_
#define _DDS_MASSDATA_LISTENER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DataReaderListener.h"
#pragma warning(disable:4275)


class DataReader;
class MassDataReader;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
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