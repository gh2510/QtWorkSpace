/************************************************************
** �ļ�����SubscriptionsDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����SubscriptionsDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_SUBSCRIPTIONSDATAREADER_H_INCLUDED_
#define _DDS_SUBSCRIPTIONSDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DataReader.h"

class Topic;
class DomainParticipant;
class DataReader;
class DataWriter;
class Subscriber;
class DataReaderListener;
class SubscriptionsDataManager;

class SubscriptionsDataReader : public DataReader 
{
public:
    SubscriptionsDataReader(
        TopicDescription* pTopic,
        const _DATA_READER_QOS *pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    virtual ~SubscriptionsDataReader() ;

    //_RETURNCODE_T Read(PublicationsSeq& receivedDataSeq, long maxSamples) ;

    _RETURNCODE_T Read_Next_Sample(_DISCOVERED_READER_DATA* pReceivedData) ;

    static SubscriptionsDataReader* Narrow(DataReader* pDataReader) ;

    //���յ�Զ��DataReader����Ϣ
    _RETURNCODE_T ReceiveRemoteReaderData(_DISCOVERED_READER_DATA* pRemoteReaderData);

    //Ϊ���ص�DataWriter��ƥ�䣨���ñ��ش洢��DataReader����Ϣ��
    _RETURNCODE_T DataWriterLocalMatch(DataWriter *pDataWriter);

    //����״̬��Ϣ
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<endl;
        return RETURNCODE_OK;
    }

    //ƥ��
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

    SubscriptionsDataManager *GetDataManger() 
    {
        return m_pDataManager;
    }

    DEF_NARROW_METHOD(SubscriptionsDataReader);

private:
    //����Զ��DataReader�б�
    SubscriptionsDataManager *m_pDataManager;

};

#endif
