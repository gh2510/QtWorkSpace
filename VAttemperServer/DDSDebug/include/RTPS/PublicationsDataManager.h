/************************************************************
** �ļ�����PublicationsDataManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����PublicationsDataManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PUBLICATIONSDATAMANAGER_H_INCLUDED_
#define _RTPS_PUBLICATIONSDATAMANAGER_H_INCLUDED_

#ifdef VXWORKS
#include "BasicTypes.h"
#include "ReturnCode.h"
#else
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "windows.h"
#include <time.h>
#endif

class DomainParticipant;
class DataReader;
class Participant;

class PublicationsDataManager
{
public:
    PublicationsDataManager(DomainParticipant *pDomainParticipant);

    virtual ~PublicationsDataManager();

    //�ж��Ƿ����µ�DataWriter
    bool IsNewDataWriter(_DISCOVERED_WRITER_DATA *pData);

    //����WriterProxy
    //���յ�һ��Զ��DataWriter���½���Ϣ�������뱾�����е�DataReaderƥ�䣬����WriterProxy
    _RETURNCODE_T WriterProxyConfigure(
        _DISCOVERED_WRITER_DATA* pData);

    //����WriterProxy
    //�����½���һ��DataReader������������Զ�˵�DataWriter��Ϣƥ�䣬����WriterProxy
    _RETURNCODE_T WriterProxyConfigure(
        DataReader* pDataReader);

    //ɾ��WriterProxy
    //���յ�Զ�˵�DataWriter��ɾ����Ϣ���ڱ�������DataReader��WriterProxy��Ѱ������Ϣ��ɾ��
    _RETURNCODE_T WriterProxyRemove(
        _DISCOVERED_WRITER_DATA* pData);

    //����
    _RETURNCODE_T AddRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteDataWriter(_PUBLICATIONS_DATA_LIST_T::iterator itData);
    //����
    _RETURNCODE_T RefreshRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //����
    _RETURNCODE_T RefreshRemoteDataWriter(
        _DISCOVERED_WRITER_DATA *pData1,
        _DISCOVERED_WRITER_DATA *pData2);

    //Զ�˵�Participant��ʱ ɾ����������DataWriter
    _RETURNCODE_T RemoteParticipantTimeout(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

	//����Զ�˷�����Ϣ�б�
	_PUBLICATIONS_DATA_LIST_T RemotePublicationsList() 
    {
		return m_pRemotePublicationsList;
	}

private:
    //���ڵ�DomainParticipant
    DomainParticipant *m_pDomainParticipant;

    //Զ��DataWriter��Ϣ����
    _PUBLICATIONS_DATA_LIST_T m_pRemotePublicationsList;

    //����
    _PUBLICATIONS_DATA_LIST_T::iterator LookupRemoteDataWriter(
        _DISCOVERED_WRITER_DATA *pData);

    //�ж��Ƿ���ͬһ��DataWriter
    bool IsSameDataWriter(
        _DISCOVERED_WRITER_DATA *pData1,
        _DISCOVERED_WRITER_DATA *pData2);

    //ΪDataReader��ƥ�� ����WriterProxy
    bool MatchDataReader(
        DataReader *pDataReader,
        _DISCOVERED_WRITER_DATA *pData);

    //�ж�DataWriter�Ƿ�����Participant
    bool Belong(_DISCOVERED_WRITER_DATA *pWriterData,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pParticipantData);
	bool Belong(_DISCOVERED_WRITER_DATA *pWriterData,
        Participant *aParticipant);


    //������
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
