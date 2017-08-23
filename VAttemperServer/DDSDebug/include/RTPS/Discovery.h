/************************************************************
** 文件名：Discovery.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-13
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 描  述：Discovery头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_DISCOVERY_H_INCLUDE_
#define _RTPS_DISCOVERY_H_INCLUDE_

#include "BasicTypes.h"
#include "ReturnCode.h"

class DomainParticipant;

class BuiltinPariticipantWriterListener;
class BuiltinPariticipantReaderListener;
class BuiltinPublicationsReaderListener;
class BuiltinSubscriptionsReaderListener;

class Topic;
class DataWriter;
class DataReader;

class ParticipantDataWriter;
class ParticipantDataReader;
class PublicationsDataWriter;
class PublicationsDataReader;
class SubscriptionsDataWriter;
class SubscriptionsDataReader;

class Discovery{
public:
    Discovery(DomainParticipant* pParticipant);

    virtual ~Discovery();

    //初始化发现模块的端点 目前为6个内置端点
    _RETURNCODE_T DiscoveryInitiation(_DURATION_T ResendPeriod);
    //删除内置端点
    _RETURNCODE_T DiscoveryRelease();

    //广播本Participant信息
    _RETURNCODE_T SendLocalParticipant();

    //广播本Participant退出的信息
    _RETURNCODE_T NotifyParticipantLogoff();

    //发送用户定义的发布端的信息
    _RETURNCODE_T SendPublicationData(
        DataWriter* pDataWriter,
        _ENTITY_STATUS_T Status);

    //发送用户定义的订阅端的信息
    _RETURNCODE_T SendSubscriptionData(
        DataReader* pDataReader,
        _ENTITY_STATUS_T Status);

    //匹配DataReader
    //本地新建DataReader后调用
    _RETURNCODE_T MatchDataReader(DataReader *pDataReader);

    //匹配DataWriter
    //本地新建DataWriter后调用
    _RETURNCODE_T MatchDataWriter(DataWriter *pDataWriter);

public:
    //获取所属的DomainParticipant
    DomainParticipant* GetRelatedParticipant() 
    {
        return m_pDomainParticipant;
    }

    //获取内置端点
    ParticipantDataWriter *GetParticipantDataWriter() 
    {
        return m_pBuiltinParticipantDataWriter;
    }
    ParticipantDataReader *GetParticipantDataReader() 
    {
        return m_pBuiltinParticipantDataReader;
    }
    PublicationsDataWriter *GetPublicationsDataWriter() 
    {
        return m_pBuiltinPublicationsDataWriter;
    }
    PublicationsDataReader *GetPublicationsDataReader() 
    {
        return m_pBuiltinPublicationsDataReader;
    }
    SubscriptionsDataWriter *GetSubscriptionsDataWriter() 
    {
        return m_pBuiltinSubscriptionsDataWriter;
    }
    SubscriptionsDataReader *GetSubscriptionsDataReader() 
    {
        return m_pBuiltinSubscriptionsDataReader;
    }

private:
    //创建内置的端点
    _RETURNCODE_T BuiltinEntityCreation(
        _DURATION_T ResendPeriod,
        _DURATION_T LeaseDuration);
    //创建主题
    _RETURNCODE_T CreateParticipantTopic();
    _RETURNCODE_T CreatePublicationsTopic();
    _RETURNCODE_T CreateSubscriptionsTopic();
    //创建内置发布者
    _RETURNCODE_T CreateParticipantDataWriter(
        _DURATION_T ResendPeriod,
        _DURATION_T LeaseDuration);
    _RETURNCODE_T CreatePublicationsDataWriter();
    _RETURNCODE_T CreateSubscriptionsDataWriter();
    //创建内置订阅者
    _RETURNCODE_T CreateParticipantDataReader();
    _RETURNCODE_T CreatePublicationsDataReader();
    _RETURNCODE_T CreateSubscriptionsDataReader();

private:
    //关联的DomainParticipant
    DomainParticipant* m_pDomainParticipant;


	//DDS层内置端点
	//2013-10-15 hjy modify 删除内置节点专用
	DataWriter* m_pParticipantDataWriter;
	DataWriter* m_pPublicationsDataWriter;
	DataWriter* m_pSubscriptionsDataWriter;

	DataReader* m_pParticipantDataReader;
	DataReader* m_pPublicationsDataReader;
	DataReader* m_pSubscriptionsDataReader;

    //DDS层内置端点
    ParticipantDataWriter* m_pBuiltinParticipantDataWriter;
    PublicationsDataWriter* m_pBuiltinPublicationsDataWriter;
    SubscriptionsDataWriter* m_pBuiltinSubscriptionsDataWriter;

    ParticipantDataReader* m_pBuiltinParticipantDataReader;
    PublicationsDataReader* m_pBuiltinPublicationsDataReader;
    SubscriptionsDataReader* m_pBuiltinSubscriptionsDataReader;

    //内置主题
    Topic* m_pDcpsParticipantTopic;
    Topic* m_pDcpsPublicationsTopic;
    Topic* m_pDcpsSubscriptionsTopic;
};

#endif
