/************************************************************
** �ļ�����DataReaderListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataReaderListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAREADERLISTENER_H_INCLUDED_
#define _DDS_DATAREADERLISTENER_H_INCLUDED_
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DDSListener.h"

class DataReader;
class DataWriter;

class DataReaderListener : public DDSListener 

{
public:
    DataReaderListener() {}
    virtual ~DataReaderListener() {}
    //�ɹ���RETURNCODE_OK
    virtual _RETURNCODE_T OnRequestedDeadlineMissed(DataReader* pDataReader, const _REQUESTED_DEADLINE_MISSED_STATUS& Status) 
    {	
        return RETURNCODE_OK;    
    }
    //�ɹ���RETURNCODE_OK
    virtual _RETURNCODE_T On_Data_Available(DataReader* pDataReader) 
    {	
        return RETURNCODE_OK;
    }
};

#endif
