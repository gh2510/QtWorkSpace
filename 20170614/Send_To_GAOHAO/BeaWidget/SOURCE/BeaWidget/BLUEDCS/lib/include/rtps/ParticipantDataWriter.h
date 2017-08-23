/************************************************************
** 文件名：ParticipantDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：ParticipantDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_PARTICIPANTDATAWRITER_H_INCLUDED_
#define _DDS_PARTICIPANTDATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DataWriter.h"

class Topic;
class DataWriterListener;
class Publisher;

class ParticipantDataWriter : public DataWriter 
{
public:
    //构造函数
    ParticipantDataWriter (Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~ParticipantDataWriter ();

    //写数据
    _RETURNCODE_T Write(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //发送数据
    _RETURNCODE_T SendParticipantData (_ENTITY_STATUS_T Status);

    //用指向DataWriter的指针构造StringDataWriter对象
    static ParticipantDataWriter* Narrow (DataWriter* pDataWriter);

    //初始化
    _RETURNCODE_T Init (_DURATION_T LeaseTime);

    DEF_NARROW_METHOD(ParticipantDataWriter);

    //发送状态信息
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"lllllllllllllllllllllllllllllllll"<<endl;
        return RETURNCODE_OK;
    }

	//2013-09-27 hjy modify 用于发送内置节点ParticipantDataWriter删除的消息
	//_RETURNCODE_T SendDeleteInfo(_ENTITY_STATUS_T Status) 
	//{
	//	DomainParticipant* pDomainParticipant = this->GetDomainParticipant();
	//	Discovery* pDiscovery= pDomainParticipant->GetRelatedDiscovery();
	//	return pDiscovery->SendPublicationData(this, Status);
	//}

    //匹配
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

private:
    //失活的时间期限
    _DURATION_T m_LeaseTime;

    //初始化 配置ReaderProxy
    _RETURNCODE_T ReaderProxyInit ();
};

#endif
