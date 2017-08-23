/************************************************************
** 文件名：Endpoint.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-10
** 修改人：无
** 日  期：无
** 描  述：Endpoint头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_ENDPOINT_H_INCLUDED_
#define _RTPS_ENDPOINT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RTPSEntity.h"

struct _ACKNACK_SUBMESSAGE;
struct _HEARTBEAT_SUBMESSAGE;
struct _DATA_SUBMESSAGE;
struct _DATA_FRAG_SUBMESSAGE;
struct _NACK_FRAG_SUBMESSAGE;

class Endpoint : public RTPSEntity 
{
public:
    //构造函数
    Endpoint ( _GUID_T Guid,
        _RELIABILITY_KIND_T ReliabilityLevel,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList) :
    RTPSEntity (Guid) 
    {
        //初始化 赋值
        m_ReliabilityLevel = ReliabilityLevel;
        m_UnicastLocatorList = UnicastLocatorList;
        m_MulticastLocatorList = MulticastLocatorList;
    }

    //析构函数
    virtual ~Endpoint () 
    {
        m_UnicastLocatorList.clear();
        m_MulticastLocatorList.clear();
    };

    //虚函数 提供报文接收接口 供重载
    //接收AckNack报文
    virtual _RETURNCODE_T AckNackMessageReceive(
        _ACKNACK_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    //接收Heartbeat报文
    virtual _RETURNCODE_T HeartbeatMessageReceive(
        _HEARTBEAT_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

	//接收Data报文
    virtual _RETURNCODE_T DataMessageReceive(
        _DATA_SUBMESSAGE *pMessage,
        _RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    //接收DataFrag报文
    virtual _RETURNCODE_T DataFragMessageReceive(
		_DATA_FRAG_SUBMESSAGE *pMessage, 
		_RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

	//接收NackFrag报文
    virtual _RETURNCODE_T NackFragMessageReceive(
		_NACK_FRAG_SUBMESSAGE *pMessage, 
		_RECEIVER *pReceiver) 
    {
        return RETURNCODE_OK;
    }

    virtual _TIME_T Deadline() 
    {
        return TIME_INFINITE;
    }

    //虚函数 检查Deadline QoS的接口
    virtual _RETURNCODE_T DeadlineCheck() 
    {
        return RETURNCODE_OK;
    };

    //获取单播地址列表
    _LOCATOR_LIST_T UnicastLocatorListGet()
    {
        return m_UnicastLocatorList;
    }

    //获取多播地址列表
    _LOCATOR_LIST_T MulticastLocatorListGet()
    {
        return m_MulticastLocatorList;
    }

    //获取一个默认单播地址
    _LOCATOR_T UnicastLocatorGet() 
    {
        if (m_UnicastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        //cout<<"Uni get:"<<m_UnicastLocatorList[0].ulAddress<<" "<<m_UnicastLocatorList[0].ulPort<<endl;
        return m_UnicastLocatorList[0];
    }

    //获取一个默认多播地址
    _LOCATOR_T MulticastLocatorGet() 
    {
        if (m_MulticastLocatorList.empty()) 
        {
            return LOCATOR_INVALID;
        }
        return m_MulticastLocatorList[0];
    }

    //获取端点的可靠程度
    _RELIABILITY_KIND_T ReliabilityKind() 
    {
        return m_ReliabilityLevel;
    }

protected:
    //可靠程度
    _RELIABILITY_KIND_T m_ReliabilityLevel;

    //单播地址列表
    _LOCATOR_LIST_T m_UnicastLocatorList;

    //多播地址列表
    _LOCATOR_LIST_T m_MulticastLocatorList;

    //主题类型，是否有键
    _TOPIC_KIND_T m_TopicKind;
};

#endif
