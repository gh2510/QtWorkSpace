/************************************************************
** 文件名：participant.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：participant头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PARTICIPANT_H_INCLUDED_
#define _RTPS_PARTICIPANT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RTPSEntity.h"

#ifndef VXWORKS   //移植
#include "Windows.h"
#endif

class DomainParticipant;
class Topic;
class TopicDescription;
class DataWriter;
class DataReader;
class HistoryCache;
class Endpoint;
class Writer;
class Reader;
class MessageProcessor;
class MessageTransmitter;
class RequestScheduler;
class ReceiveBuffer;
struct _DATA_SUBMESSAGE;
struct _DATA_FRAG_SUBMESSAGE;
struct _HEARTBEAT_SUBMESSAGE;
struct _ACKNACK_SUBMESSAGE;
struct _NACK_FRAG_SUBMESSAGE;
class Participant : public RTPSEntity 
{
public:
    //构造函数
    Participant (_GUID_T Guid,
        _IP_LIST_T DefaultIpList,
        DomainParticipant *pDomainParticipant);

    //析构函数
    virtual ~Participant ();

	void StartTasks();

	void StopRequestExcute();

    //结束任务
    _RETURNCODE_T DeleteSendTask();
    _RETURNCODE_T DeleteReceiveTask();
    _RETURNCODE_T DeleteDispatchTask();

    //创建发布端映射 Writer
    Writer *CreateWriter (
        HistoryCache *pHistoryCache,
        DataWriter *pDataWriter,
        Topic *pTopic,
        const _DATA_WRITER_QOS *pQos);

    //删除发布端映射 Writer
    _RETURNCODE_T DeleteWriter (Writer *pWriter);

    //创建订阅端映射 Reader
    Reader *CreateReader (
        HistoryCache *pHistoryCache,
        DataReader *pDataReader,
        TopicDescription *pTopic,
        const _DATA_READER_QOS *pQos);

    //删除订阅端映射 Reader
    _RETURNCODE_T DeleteReader (Reader *pReader);

    //查找端点，包括Writer和Reader
    Endpoint *EndpointLookup (_GUID_T Guid);

	//查找端点，并接收数据
	_RETURNCODE_T EndpointDataMessageReceive(_GUID_T Guid, _DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收多播数据
	_RETURNCODE_T EndpointMulticastDataMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收分片数据
	_RETURNCODE_T EndpointDataFragMessageReceive(_GUID_T Guid, _DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收多播分片数据
	_RETURNCODE_T EndpointMulticastDataFragMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

	//查找端点，并接收heartbeat数据
	_RETURNCODE_T EndpointHeartbeatMessageReceive(_GUID_T Guid, _HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收多播heartbeat数据
	_RETURNCODE_T EndpointMulticastHeartbeatMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收AckNack数据
	_RETURNCODE_T EndpointAckNackMessageReceive(_GUID_T Guid, _ACKNACK_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//查找端点，并接收nackFrag数据
	_RETURNCODE_T EndpointNackFragMessageReceive(_GUID_T Guid, _NACK_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    bool EndpointExist(Endpoint *pEndpoint);

    //获取内置端点使用的单播地址列表
    _LOCATOR_LIST_T MetatrafficUnicastLocatorList() 
    {
        return m_MetatrafficUnicastLocatorList;
    }

    //获取内置端点使用的多播地址列表
    _LOCATOR_LIST_T MetatrafficMulticastLocatorList() 
    {
        return m_MetatrafficMulticastLocatorList;
    }

    //获取默认单播地址列表
    _LOCATOR_LIST_T DefaultUnicastLocatorList() 
    {
        return m_DefaultUnicastLocatorList;
    }

    //获取默认多播地址列表
    _LOCATOR_LIST_T DefaultMulticastLocatorList() 
    {
        return m_DefaultMulticastLocatorList;
    }

    //获取协议版本号
    _PROTOCOL_VERSION_T ProtocolVersion() 
    {
        return m_ProtocolVersion;
    }

    //获取厂商编号
    _VENDOR_ID_T VendorId() 
    {
        return m_VendorId;
    }

    MessageProcessor *GetMessageProcessor() 
    {
        return m_pMessageProcessor;
    }

    MessageTransmitter *GetMessageTransmitter () 
    {
        return m_pMessageTransmitter;
    }

	//2015-3-17 hjy add multi network card support
	DomainParticipant *GetRelatedDomainParticipant() 
	{
		return m_pRelatedDomainParticipant;
	}

    //多播过程中查找订阅端映射列表
    _ENDPOINT_LIST_T EndpointMulticastLookup(unsigned long ulMulticastAddress, _GUID_T WriterGUID);
    
    //根据主题名计算多播地址
    _RETURNCODE_T MulticastLocatorGenerate (const char* pTopicName, _LOCATOR_T* pMultiLocator);

	RequestScheduler** GetRequestScheduler()
    {
		return m_pScheduleList;
	}

	//大数据
	bool isBusy();
		//获取线程ID
#ifdef VXWORKS
	int GetSendTaskId()
    {
        return m_hSendTaskId;
    }
#else
	HANDLE GetSendTaskId()
    {
        return m_hSendTaskId;
    }
#endif

private:
    //初始化Locator
    _RETURNCODE_T LocatorInitial(_IP_LIST_T DefaultIpList);

#ifdef VXWORKS   //移植
    //启动发送线程/任务
    int SendTaskStart();

    //启动接收线程/任务
    int ReceiveTaskStart();

    //启动分发处理线程/任务
    int DispatchTaskStart();

#else
	HANDLE SendTaskStart();
	HANDLE ReceiveTaskStart();
	HANDLE DispatchTaskStart();
#endif

private:
    //RTPS协议 版本
    _PROTOCOL_VERSION_T m_ProtocolVersion;

    //生产厂商编号
    _VENDOR_ID_T m_VendorId;

    //默认单播地址列表
    _LOCATOR_LIST_T m_DefaultUnicastLocatorList;

    //默认多播地址列表
    _LOCATOR_LIST_T m_DefaultMulticastLocatorList;

    //内置端点使用的单播地址列表
    _LOCATOR_LIST_T m_MetatrafficUnicastLocatorList;

    //内置端点使用的多播地址列表
    _LOCATOR_LIST_T m_MetatrafficMulticastLocatorList;

    //对应的DDS DomainParticipant
    DomainParticipant* m_pRelatedDomainParticipant;

    //包含的端点（Writer/Reader）列表
    _ENDPOINT_LIST_T m_EndpointList;

    //调度队列，0为ImmeditRequestScheduler，1为PeriodRequestScheduler
    RequestScheduler** m_pScheduleList;

    //接收缓冲区
    ReceiveBuffer* m_pReceiveBuffer;

    //报文处理端
    MessageProcessor* m_pMessageProcessor;

    //报文传输端
    MessageTransmitter *m_pMessageTransmitter;

    //任务ID
#ifdef VXWORKS   //移植
	int m_hSendTaskId;
	int m_hReceiveTaskId;
	int m_hDispatchTaskId;
#else
	HANDLE m_hSendTaskId;
	HANDLE m_hReceiveTaskId;
	HANDLE m_hDispatchTaskId;
#endif

    //互斥锁 互斥访问对象为m_EndpointList及m_EndpointMultiAddrList
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

    //多播地址与端点映射对应关系
    _ENDPOINT_MULTI_ADDR_LIST_T m_EndpointMultiAddrList;
};

#endif
