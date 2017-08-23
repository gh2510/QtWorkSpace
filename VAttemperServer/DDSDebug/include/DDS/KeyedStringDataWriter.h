/************************************************************
** �ļ�����KeyedStringDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����KeyedStringDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRINGDATAWRITER_H_INCLUDED_
#define _DDS_KEYEDSTRINGDATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "mr/MRBasicTypes.h"
#include "DDS/DataWriter.h"
#include "dds/KeyedString.h"
#include "APP/APP.h"

class Topic;
class DataWriterListener;
class Publisher;

class KeyedStringDataWriter : public DataWriter
{
public:
    //���캯��
    KeyedStringDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //��������
    virtual ~KeyedStringDataWriter ();

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
    _RETURNCODE_T Write(KEYED_STRING Data, _INSTANCE_HANDLE_T Handle);

    //��ָ��DataWriter��ָ�빹��StringDataWriter����
    static KeyedStringDataWriter* Narrow(DataWriter* pDataWriter);

    DEF_NARROW_METHOD(KeyedStringDataWriter);

    //ע��ʵ��
    _INSTANCE_HANDLE_T Register_Instance(KEYED_STRING Instance);

    //ע��ʵ��
    _RETURNCODE_T Unregister_Instance(KEYED_STRING Instance, _INSTANCE_HANDLE_T Handle);

    //ȡ��ֵ
    _RETURNCODE_T Get_Key_Value(_KEYED_STRING_KEY_HOLDER& Key_holder, _INSTANCE_HANDLE_T Handle);

    //��ѯʵ��
    _INSTANCE_HANDLE_T Lookup_Instance(KEYED_STRING Instance);

    //ɾ��ʵ��
    _RETURNCODE_T Dispose(KEYED_STRING Instance, _INSTANCE_HANDLE_T Handle);

private:
#ifdef _APP_FAULT_TOLERANT_
    //�Ƿ���Ҫ�ݴ���
    bool m_bFtEnable;
#endif
    //Ӧ�����������
    char *m_pAppName;

    //InstanceHandle��keyholder��ӳ��
    _INSTANCE_HANDLE_TO_KEY_HOLDER m_InstanceHandletoKeyHolder;

};

#endif
