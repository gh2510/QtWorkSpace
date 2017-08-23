//������
/************************************************************
** �ļ�����MassDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2013-07-22
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MassDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREADER_H_INCLUDED_
#define _DDS_MASSDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataReader.h"
#include "APP/APP.h"

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class MassDataReader : public DataReader
{
#else
class DDS_DLL MassDataReader : public DataReader
{
#endif
public:
    //���캯��
    MassDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //��������
    virtual ~MassDataReader();

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


    //������Ҫ��ȡ����һ������
    //_RETURNCODE_T Read_Next_Sample(_DDS_STRING* receivedData, _SAMPLE_INFO& sampleInfo);

	_RETURNCODE_T ReceiveData(char *Data,unsigned long len);
    _RETURNCODE_T Read_Next_Sample(char *&ReceivedData, unsigned long &len);
	_RETURNCODE_T DataNotify(_GUID_T writerID,unsigned long DataNum);
	_RETURNCODE_T Read_Next_Data(char *&ReceivedData, unsigned long &len);

    //��ָ��DataReader��ָ�빹��MassDataReader����
    static MassDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(MassDataReader);

private:
	//Ӧ�����������
    char *m_pAppName;
	_MASS_FRAGMENT_DATA_LIST_T m_FragmentDataList;
	_MASS_DATA_LIST_T m_DataList;

};

#endif
