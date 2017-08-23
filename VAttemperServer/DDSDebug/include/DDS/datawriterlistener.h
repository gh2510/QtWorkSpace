/************************************************************
** �ļ�����DataWriterListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataWriterListenerͷ�ļ�
** ��  ����Version 0.1
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
    //�ɹ��򷵻�RETURNCODE_OK
    virtual _RETURNCODE_T On_Offered_Deadline_Missed(DataWriter* pDataWriter, const _OFFERED_DEADLINE_MISSED_STATUS& Status) 
    {	
        return RETURNCODE_OK;    
    }
};

#endif
