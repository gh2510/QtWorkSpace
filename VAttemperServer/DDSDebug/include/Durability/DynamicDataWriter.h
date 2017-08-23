/************************************************************
** �ļ�����DynamicDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-03-30
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DynamicDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DYNAMICDATAWRITER_H_INCLUDED_
#define _DDS_DYNAMICDATAWRITER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"

class Topic;
class DataWriterListener;
class Publisher;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DynamicDataWriter : public DataWriter 
{
#else
class DDS_DLL DynamicDataWriter : public DataWriter 
{
#endif
public:
    //���캯��
    DynamicDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //��������
    virtual ~DynamicDataWriter();

	//��Ӧ�����
	_RETURNCODE_T AppSet(const char *pAppName);

#ifdef _APP_FAULT_TOLERANT_
    //�ݴ�����
    _RETURNCODE_T FaultTolerantSet();
#endif

#ifdef _APP_FAULT_TOLERANT_
    //�ݴ��ж�
    bool FaultTolerantJudge();
#endif

#ifdef _APP_DATA_RECORD_
	//��¼���ݷ��ͽ���
	_RETURNCODE_T RecordData(_SEQUENCE_NUM SeqNum);
#endif

#ifdef _APP_SERVICE_MONITOR_
	//��¼�����Ϣ
	_RETURNCODE_T MonitorService(_TOPIC_STATUS Status);
#endif

    //д����
    _RETURNCODE_T Write(char* pData, unsigned long ulLen);

    //��ָ��DataWriter��ָ�빹��StringDataWriter����
    static DynamicDataWriter* Narrow(DataWriter* pDataWriter);

    DEF_NARROW_METHOD(DynamicDataWriter);

private:
#ifdef _APP_FAULT_TOLERANT_
    //�Ƿ���Ҫ�ݴ���
    bool m_bFtEnable;
#endif
    //Ӧ�����������
    char *m_pAppName;

};

#endif
