/************************************************************
** 文件名：SubscriptionsDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：SubscriptionsDataReader头文件
** 版  本：Version 0.1
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

    //接收到远端DataReader的信息
    _RETURNCODE_T ReceiveRemoteReaderData(_DISCOVERED_READER_DATA* pRemoteReaderData);

    //为本地的DataWriter做匹配（利用本地存储的DataReader的信息）
    _RETURNCODE_T DataWriterLocalMatch(DataWriter *pDataWriter);

    //发送状态信息
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<endl;
        return RETURNCODE_OK;
    }

    //匹配
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
    //保存远程DataReader列表
    SubscriptionsDataManager *m_pDataManager;

};

#endif
