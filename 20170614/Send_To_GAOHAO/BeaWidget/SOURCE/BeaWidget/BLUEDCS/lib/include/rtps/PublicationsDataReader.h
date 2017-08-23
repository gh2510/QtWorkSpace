/************************************************************
** 文件名：PublicationsDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：PublicationsDataReader头文件
** 版  本：Version 0.1
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

    //接收到远端DataWriter的信息
    _RETURNCODE_T ReceiveRemoteWriterData(_DISCOVERED_WRITER_DATA* pRemoteWriterData);

    //为本地的DataReader做匹配（利用本地存储的DataWriter的信息）
    _RETURNCODE_T DataReaderLocalMatch(DataReader *pDataReader);

    //发送状态信息
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"jjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<endl;
        return RETURNCODE_OK;
    }

    //匹配
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
    //保存远程DataWriter列表
    PublicationsDataManager *m_pDataManager;
};

#endif
