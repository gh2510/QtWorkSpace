/************************************************************
** �ļ�����participant.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����participantͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PARTICIPANT_H_INCLUDED_
#define _RTPS_PARTICIPANT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/RTPSEntity.h"

#ifndef VXWORKS   //��ֲ
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
    //���캯��
    Participant (_GUID_T Guid,
        _IP_LIST_T DefaultIpList,
        DomainParticipant *pDomainParticipant);

    //��������
    virtual ~Participant ();

	void StartTasks();

	void StopRequestExcute();

    //��������
    _RETURNCODE_T DeleteSendTask();
    _RETURNCODE_T DeleteReceiveTask();
    _RETURNCODE_T DeleteDispatchTask();

    //����������ӳ�� Writer
    Writer *CreateWriter (
        HistoryCache *pHistoryCache,
        DataWriter *pDataWriter,
        Topic *pTopic,
        const _DATA_WRITER_QOS *pQos);

    //ɾ��������ӳ�� Writer
    _RETURNCODE_T DeleteWriter (Writer *pWriter);

    //�������Ķ�ӳ�� Reader
    Reader *CreateReader (
        HistoryCache *pHistoryCache,
        DataReader *pDataReader,
        TopicDescription *pTopic,
        const _DATA_READER_QOS *pQos);

    //ɾ�����Ķ�ӳ�� Reader
    _RETURNCODE_T DeleteReader (Reader *pReader);

    //���Ҷ˵㣬����Writer��Reader
    Endpoint *EndpointLookup (_GUID_T Guid);

	//���Ҷ˵㣬����������
	_RETURNCODE_T EndpointDataMessageReceive(_GUID_T Guid, _DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬�����նಥ����
	_RETURNCODE_T EndpointMulticastDataMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬�����շ�Ƭ����
	_RETURNCODE_T EndpointDataFragMessageReceive(_GUID_T Guid, _DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬�����նಥ��Ƭ����
	_RETURNCODE_T EndpointMulticastDataFragMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

	//���Ҷ˵㣬������heartbeat����
	_RETURNCODE_T EndpointHeartbeatMessageReceive(_GUID_T Guid, _HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬�����նಥheartbeat����
	_RETURNCODE_T EndpointMulticastHeartbeatMessageReceive(unsigned long ulMulticastAddress, _GUID_T WriterGUID, _HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬������AckNack����
	_RETURNCODE_T EndpointAckNackMessageReceive(_GUID_T Guid, _ACKNACK_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);
	//���Ҷ˵㣬������nackFrag����
	_RETURNCODE_T EndpointNackFragMessageReceive(_GUID_T Guid, _NACK_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    bool EndpointExist(Endpoint *pEndpoint);

    //��ȡ���ö˵�ʹ�õĵ�����ַ�б�
    _LOCATOR_LIST_T MetatrafficUnicastLocatorList() 
    {
        return m_MetatrafficUnicastLocatorList;
    }

    //��ȡ���ö˵�ʹ�õĶಥ��ַ�б�
    _LOCATOR_LIST_T MetatrafficMulticastLocatorList() 
    {
        return m_MetatrafficMulticastLocatorList;
    }

    //��ȡĬ�ϵ�����ַ�б�
    _LOCATOR_LIST_T DefaultUnicastLocatorList() 
    {
        return m_DefaultUnicastLocatorList;
    }

    //��ȡĬ�϶ಥ��ַ�б�
    _LOCATOR_LIST_T DefaultMulticastLocatorList() 
    {
        return m_DefaultMulticastLocatorList;
    }

    //��ȡЭ��汾��
    _PROTOCOL_VERSION_T ProtocolVersion() 
    {
        return m_ProtocolVersion;
    }

    //��ȡ���̱��
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

    //�ಥ�����в��Ҷ��Ķ�ӳ���б�
    _ENDPOINT_LIST_T EndpointMulticastLookup(unsigned long ulMulticastAddress, _GUID_T WriterGUID);
    
    //��������������ಥ��ַ
    _RETURNCODE_T MulticastLocatorGenerate (const char* pTopicName, _LOCATOR_T* pMultiLocator);

	RequestScheduler** GetRequestScheduler()
    {
		return m_pScheduleList;
	}

	//������
	bool isBusy();
		//��ȡ�߳�ID
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
    //��ʼ��Locator
    _RETURNCODE_T LocatorInitial(_IP_LIST_T DefaultIpList);

#ifdef VXWORKS   //��ֲ
    //���������߳�/����
    int SendTaskStart();

    //���������߳�/����
    int ReceiveTaskStart();

    //�����ַ������߳�/����
    int DispatchTaskStart();

#else
	HANDLE SendTaskStart();
	HANDLE ReceiveTaskStart();
	HANDLE DispatchTaskStart();
#endif

private:
    //RTPSЭ�� �汾
    _PROTOCOL_VERSION_T m_ProtocolVersion;

    //�������̱��
    _VENDOR_ID_T m_VendorId;

    //Ĭ�ϵ�����ַ�б�
    _LOCATOR_LIST_T m_DefaultUnicastLocatorList;

    //Ĭ�϶ಥ��ַ�б�
    _LOCATOR_LIST_T m_DefaultMulticastLocatorList;

    //���ö˵�ʹ�õĵ�����ַ�б�
    _LOCATOR_LIST_T m_MetatrafficUnicastLocatorList;

    //���ö˵�ʹ�õĶಥ��ַ�б�
    _LOCATOR_LIST_T m_MetatrafficMulticastLocatorList;

    //��Ӧ��DDS DomainParticipant
    DomainParticipant* m_pRelatedDomainParticipant;

    //�����Ķ˵㣨Writer/Reader���б�
    _ENDPOINT_LIST_T m_EndpointList;

    //���ȶ��У�0ΪImmeditRequestScheduler��1ΪPeriodRequestScheduler
    RequestScheduler** m_pScheduleList;

    //���ջ�����
    ReceiveBuffer* m_pReceiveBuffer;

    //���Ĵ����
    MessageProcessor* m_pMessageProcessor;

    //���Ĵ����
    MessageTransmitter *m_pMessageTransmitter;

    //����ID
#ifdef VXWORKS   //��ֲ
	int m_hSendTaskId;
	int m_hReceiveTaskId;
	int m_hDispatchTaskId;
#else
	HANDLE m_hSendTaskId;
	HANDLE m_hReceiveTaskId;
	HANDLE m_hDispatchTaskId;
#endif

    //������ ������ʶ���Ϊm_EndpointList��m_EndpointMultiAddrList
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

    //�ಥ��ַ��˵�ӳ���Ӧ��ϵ
    _ENDPOINT_MULTI_ADDR_LIST_T m_EndpointMultiAddrList;
};

#endif
