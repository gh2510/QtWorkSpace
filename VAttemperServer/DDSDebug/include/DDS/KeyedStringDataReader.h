/************************************************************
** �ļ�����KeyedStringDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����KeyedStringDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRINGDATAREADER_H_INCLUDED_
#define _DDS_KEYEDSTRINGDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "mr/MRBasicTypes.h"
#include "DDS/DataReader.h"
#include "dds/KeyedString.h"
#include "APP/APP.h"


class KeyedStringDataReader : public DataReader
{
public:
    //���캯��
    KeyedStringDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //��������
    virtual ~KeyedStringDataReader();

    //��Ӧ�����
    _RETURNCODE_T AppSet(const char *pAppName);

#ifdef _APP_DATA_RECORD_
	//��¼���ݷ��ͽ���
	_RETURNCODE_T RecordData(_SEQUENCE_NUM SeqNum);
#endif
	
#ifdef _APP_SERVICE_MONITOR_
	//��¼�����Ϣ
	_RETURNCODE_T MonitorService(_TOPIC_STATUS Status);
#endif

    //������Ҫ��ȡ����������
    _RETURNCODE_T Read(_KEYED_STRING_SEQ& ReceivedDataSeq, _SAMPLE_INFO_SEQ& InfoSeq, long lMaxSamples);

    //������Ҫ��ȡ����һ������
    _RETURNCODE_T Read_Next_Sample(KEYED_STRING* pReceivedData, _SAMPLE_INFO& SampleInfo);

    //��ָ��DataReader��ָ�빹��StringDataReader����
    static KeyedStringDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(KeyedStringDataReader);

    //������Ҫ��ȡ������ʵ������
    _RETURNCODE_T Read_Instance(_KEYED_STRING_SEQ& ReceivedDataSeq,
        _SAMPLE_INFO_SEQ & InfoSeq,
        _INSTANCE_HANDLE_T Handle,
        long lMaxSamples);

    //������Ҫ��ȡ����һ��ʵ������������
    _RETURNCODE_T Read_Next_Instance(_KEYED_STRING_SEQ& ReceivedDataSeq,
        _SAMPLE_INFO_SEQ & InfoSeq,
        _INSTANCE_HANDLE_T Previous_handle,
        long lMaxSamples);

    //��ѯʵ��
    _INSTANCE_HANDLE_T Lookup_Instance(KEYED_STRING Instance);

    //ȡ��ֵ
    _RETURNCODE_T Get_Key_Value(_KEYED_STRING_KEY_HOLDER& Key_holder, _INSTANCE_HANDLE_T Handle);

private:
	//Ӧ�����������
    char *m_pAppName;

    //InstanceHandle��keyholder��ӳ��
    _INSTANCE_HANDLE_TO_KEY_HOLDER m_InstanceHandletoKeyHolder;

};

#endif
