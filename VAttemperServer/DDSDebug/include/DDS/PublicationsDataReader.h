/************************************************************
** �ļ�����PublicationsDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����PublicationsDataReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_PUBLICATIONSDATAREADER_H_INCLUDED_
#define _DDS_PUBLICATIONSDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DataReader.h"

class PublicationsDataManager;
class Subscriber;

//typedef list<Publications> PublicationsSeq;

class PublicationsDataReader : public DataReader 
{
public:
    PublicationsDataReader(
        TopicDescription* pTopic,
        const _DATA_READER_QOS *pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    virtual ~PublicationsDataReader() ;

   // _RETURNCODE_T read(PublicationsSeq& receivedDataSeq, long maxSamples) ;

    _RETURNCODE_T Read_Next_Sample(_DISCOVERED_WRITER_DATA* pReceivedData) ;

    static PublicationsDataReader* Narrow(DataReader* pDataReader) ;

    //���յ�Զ��DataWriter����Ϣ
    _RETURNCODE_T ReceiveRemoteWriterData(_DISCOVERED_WRITER_DATA* pRemoteWriterData);

    //Ϊ���ص�DataReader��ƥ�䣨���ñ��ش洢��DataWriter����Ϣ��
    _RETURNCODE_T DataReaderLocalMatch(DataReader *pDataReader);

    //����״̬��Ϣ
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"<<endl;
        return RETURNCODE_OK;
    }

    //ƥ��
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

    PublicationsDataManager *GetDataManger () 
    {
        return m_pDataManager;
    }

    DEF_NARROW_METHOD(PublicationsDataReader);

private:
    //����Զ��DataWriter�б�
    PublicationsDataManager *m_pDataManager;
};

#endif
