/************************************************************
** �ļ�����StringDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-16
** �޸��ˣ���
** ��  �ڣ���
** ��  ����StringDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_STRINGDATAREADER_H_INCLUDED_
#define _DDS_STRINGDATAREADER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataReader.h"
#include "APP/APP.h"

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class StringDataReader : public DataReader
{
#else
class DDS_DLL StringDataReader : public DataReader
{
#endif
public:
    //���캯��
    StringDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //��������
    virtual ~StringDataReader();

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
    //_RETURNCODE_T Read(_STRING_SEQ& receivedDataSeq, _SAMPLE_INFO_SEQ& infoSeq, long maxSamples);
    _RETURNCODE_T Read(_STRING_SEQ& ReceivedDataSeq, long lMaxSamples);

    //������Ҫ��ȡ����һ������
    //_RETURNCODE_T Read_Next_Sample(_DDS_STRING* receivedData, _SAMPLE_INFO& sampleInfo);
    _RETURNCODE_T Read_Next_Sample(_DDS_STRING& ReceivedData);

    //��ָ��DataReader��ָ�빹��StringDataReader����
    static StringDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(StringDataReader);

private:
	//Ӧ�����������
    char *m_pAppName;

};

#endif
