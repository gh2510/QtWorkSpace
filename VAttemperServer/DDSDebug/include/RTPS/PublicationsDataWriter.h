/************************************************************
** 文件名：PublicationsDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：PublicationsDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_PUBLICATIONSDATAWRITER_H_INCLUDED_
#define _DDS_PUBLICATIONSDATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataWriter.h"

class Topic;
class DataWriterListener;
class Publisher;

class PublicationsDataWriter : public DataWriter 
{
public:
    PublicationsDataWriter(Topic* pTopic,
               const _DATA_WRITER_QOS *pQos,
               DataWriterListener* pListener,
               _STATUS_MASK Mask,
               Publisher* pPublisher,
               unsigned long ulCacheLength);

    virtual ~PublicationsDataWriter() ;

    static PublicationsDataWriter* Narrow(DataWriter* pDataWriter) ;

    _RETURNCODE_T Write(_DISCOVERED_WRITER_DATA* pWriterData);

    _RETURNCODE_T SendDataWriter(DataWriter* pDataWriter,_ENTITY_STATUS_T Status);

    //重写内置writer的WriteFinished函数，不删除HistoryCache中任何记录
    virtual _RETURNCODE_T WriteFinished(_SEQUENCE_NUMBER_T SeqNum);

    //发送状态信息
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
        return RETURNCODE_OK;
    }

    //匹配
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

    DEF_NARROW_METHOD(PublicationsDataWriter);

private:
    //DomainParticipant* m_domainParticipant;
};

#endif
