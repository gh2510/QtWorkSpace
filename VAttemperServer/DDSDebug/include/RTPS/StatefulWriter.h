/************************************************************
** �ļ�����StatefulWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-12
** �޸��ˣ���
** ��  �ڣ���
** ��  ����StatefulWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_STATEFULWRITER_INCLUDED_H
#define _RTPS_STATEFULWRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Writer.h"
#include "rtps/Message.h"

class RequestScheduler;
class ReaderProxy;

class StatefulWriter : public Writer
{
public:
    //���캯��
    StatefulWriter(_GUID_T Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList,
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache*     pHistoryCache,
        DataWriter*       pDataWriter,
        RequestScheduler  **pScheduleList);

    //��������
    virtual ~StatefulWriter();

    //���ȶ��г�ʼ��
    _RETURNCODE_T ScheduleListInit();

    //���ƥ��Ķ��Ķ˴���
    _RETURNCODE_T MatchedReaderAdd( ReaderProxy* pReaderProxy);

    //ɾ��ƥ��Ķ��Ķ˴���
    _RETURNCODE_T MatchedReaderRemove( ReaderProxy* pReaderProxy);

    //ɾ���ض�ǰ׺�Ķ��Ķ˴���
    //_RETURNCODE_T MatchedReaderRemove(_GUID_PREFIX_T GuidPrefix);

	//������ 2013-09-04 �޸�
	int GetMatchDataReaderNum()
	{
		return m_MatchedReaderList.size();
	}

	//������ 2013-09-04 ��ȡ������
#ifdef VXWORKS 
	SEM_ID GetMutex() 
	{ 
		return m_hProxySemMutex; 
	}
#else
	HANDLE GetMutex() 
	{ 
		return m_hProxySemMutex; 
	}
#endif

    //��ѯƥ��Ķ��Ķ˴���
    ReaderProxy* MatchedReaderLookup( _GUID_T AReaderGuid);

    //��ѯ�����Ƿ����ж��Ķ�ȷ��
    bool IsAckedByAll( _SEQUENCE_NUMBER_T SequenceNumber);

    //��ѯ�Ƿ���Ҫ���Ķ˷���Heartbeat
    bool NeedHeartbeat(ReaderProxy *pReaderProxy);

    //��ȡHeartbeat���ĵ�Ŀ�Ķ� ��ReaderProxy��δ���յ��������ݣ�
    _RETURNCODE_T HeartbeatDestGet(_READER_PROXY_LIST &List);

    //����Ƿ�����Deadline QoS
    _RETURNCODE_T DeadlineCheck();

    //�������ݷ��� ��DDSDataWriter����
    _RETURNCODE_T DataSend(_CACHE_CHANGE *pNewChange);

    //����Heartbeat����
    _RETURNCODE_T HeartbeatMessageGet( char** pMessage, unsigned long *pLength, ReaderProxy *pReaderProxy);

    //����Data����
    _RETURNCODE_T DataMessageGet( char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList, ReaderProxy* pReaderProxy);

    //����Data�ಥ����
    _RETURNCODE_T DataMessageMultiGet(char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList);

    //����AckNack����
    _RETURNCODE_T AckNackMessageReceive( _ACKNACK_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    RequestScheduler** GetScheduleList()
    { 
        return m_pScheduleList;
    }

    _RETURNCODE_T DataSendFinish();

	//�Ƿ��ȡ�ಥ
	bool IsMulticast();

	//���ݷ�Ƭ
	_RETURNCODE_T DataIntoFrag(char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, _CACHE_CHANGE* pSendChange, _ENTITYID ReaderID);

	//���ݷ�Ƭ�޸�
	_RETURNCODE_T FragRepairMessageGet( char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, ReaderProxy* pReaderProxy, _SEQUENCE_NUMBER_T WriterSN, _FRAGMENT_NUMBER_SET _FRAGMENT_NUMBER_SET);

	//����NackFrag����
	_RETURNCODE_T NackFragMessageReceive( _NACK_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

private:
    //ƥ��Ķ��Ķ˴����б�
    _READER_PROXY_LIST m_MatchedReaderList; //�޸�

	//2014-02-28 hjy modify �������͵�HeartBeat����,ÿ50�����һ��,Ȼ������
	unsigned long SendHeartbeatCount;

	//2014-02-28 hjy modify �������յ�ack�ı��ĸ���,ÿ50�����һ��,Ȼ������
	/*unsigned long ReceiveAckCount;*/


    //������ ������ʶ���ΪProxy
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hProxySemMutex;
#else
	HANDLE m_hProxySemMutex;
#endif

    //������ ������ʶ���ΪDataMessageGet
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMsgGetMutex;
#else
	HANDLE m_hSemMsgGetMutex;
#endif

	//������ ������ʶ���Ϊhistorycache
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemCacheMutex;
#else
	HANDLE m_hSemCacheMutex;
#endif

	//������ ������ʶ���ΪDataMessageGet
//#ifdef VXWORKS   //��ֲ
//	SEM_ID m_hSemHistoryCacheMutex;
//#else
//	HANDLE m_hSemHistoryCacheMutex;
//#endif
};

#endif
