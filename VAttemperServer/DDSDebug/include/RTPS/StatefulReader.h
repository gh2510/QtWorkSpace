/************************************************************
** �ļ�����StatefulReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����StatefulReaderͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_STATEFULREADER_H_INCLUDED_
#define _RTPS_STATEFULREADER_H_INCLUDED_

#include "BasicTypes.h"
#include "rtps/Reader.h"
#include "rtps/Message.h"

class WriterProxy;
class RequestScheduler;

class StatefulReader : public Reader 
{
public:
    //���캯��
    StatefulReader (
        _GUID_T Guid,
        _LOCATOR_LIST_T UnicastLocatorList,
        _LOCATOR_LIST_T MulticastLocatorList,
        const _DATA_READER_QOS* pQos,
        RequestScheduler** pRequestScheduler,
        DataReader *pDataReader,
        HistoryCache *pHistoryCache);

    //��������
    virtual ~StatefulReader ();

    //���ȶ��г�ʼ��
    _RETURNCODE_T ScheduleListInit();

    //����ƥ��ķ����˴���
    _RETURNCODE_T MatchedWriterAdd (WriterProxy *pWriterProxy);

    //ɾ��ƥ��ķ����˴���
    _RETURNCODE_T MatchedWriterRemove (WriterProxy *pWriterProxy);

    //ɾ���ض�ǰ׺�ķ����˴���
    //_RETURNCODE_T MatchedWriterRemove (_GUID_PREFIX_T GuidPrefix);

    //��ѯƥ��ķ����˴���
    WriterProxy *MatchedWriterLookup (_GUID_T Guid);

    //���Deadline QoS�Ƿ�����
    _RETURNCODE_T DeadlineCheck ();

    //����Data����
    _RETURNCODE_T DataMessageReceive (_DATA_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

	//����DataFrag����
	_RETURNCODE_T DataFragMessageReceive(_DATA_FRAG_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    //����Heartbeat����
    _RETURNCODE_T HeartbeatMessageReceive (_HEARTBEAT_SUBMESSAGE *pMessage, _RECEIVER *pReceiver);

    //����AckNack����
    _RETURNCODE_T AckNackMessageGet (char **pMessage, unsigned long *ulLength, WriterProxy *writerProxy);

    //���m_MatchedWriter���Ƿ�����ض�writerProxy
    bool WriterProxyExist (_GUID_T WriterGUID);

	//�������ݷ�Ƭ�б���
	unsigned long FragmentDataListSizeGet() 
    {
		return m_FragmentDataList.size();
	}

	//����ض���ŵ����ݷ�Ƭ����״̬
	_RETURNCODE_T FragNumberSetGet(_GUID_T WriterGuid, _SEQUENCE_NUMBER_T MissingNum, _FRAGMENT_NUMBER_SET* pFragNackState);

	//ƥ��ķ����߸���
	unsigned long MatchedWriterNum()
    {
		return m_MatchedWriter.size();
	}

	RequestScheduler** GetRequestScheduler() 
    {
		return m_pScheduleList;
	}

	//2013-11-04 hjy modify
	//���ػ����� ������ʶ���Ϊm_MatchedWriter
#ifdef VXWORKS   //��ֲ
	SEM_ID GetStatefulReaderMutex()
	{
		return m_hSemMutex;
	}
#else
	HANDLE GetStatefulReaderMutex()
	{
		return m_hSemMutex;
	}
#endif

private:
    //Զ��Writer�����б�
    _WRITER_PROXY_LIST_T m_MatchedWriter;

	//���ݷ�Ƭ�б�
	_FRAGMENT_DATA_LIST_T m_FragmentDataList;

	//�����±��ĵĽ�ֹ��
    _DURATION_T m_FragDeadline;

    //������ ������ʶ���ΪProxy
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

	//���ݷ�Ƭ��
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemFragMutex;
#else
	HANDLE m_hSemFragMutex;
#endif

};

#endif
