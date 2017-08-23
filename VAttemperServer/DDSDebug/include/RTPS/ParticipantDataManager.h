/************************************************************
** �ļ�����ParticipantDataManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ParticipantDataManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PARTICIPANTDATAMANAGER_H_INCLUDED_
#define _RTPS_PARTICIPANTDATAMANAGER_H_INCLUDED_

#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#pragma comment(lib,"ws2_32.lib") 
#include "Windows.h"
#endif

#include "BasicTypes.h"
#include "ReturnCode.h"

typedef list<_SPDP_DISCOVERED_PARTICIPANT_DATA *> _PARTICIPANT_DATALIST_T;

class DomainParticipant;

class ParticipantDataManager
{
public:
    ParticipantDataManager(DomainParticipant *pDomainParticipant);

    virtual ~ParticipantDataManager();

    //�ж��Ƿ����µ�Participant
    bool IsNewParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //�������ö˵��Proxy
    _RETURNCODE_T BuiltinEntityProxyConfigure(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //ɾ�����ö˵��Proxy
    _RETURNCODE_T BuiltinEntityProxyRemove(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //ɾ���û��˵��Proxy
    _RETURNCODE_T UserEntityProxyRemove(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //���Participant�Ƿ���� �߳���ڵ�ַ
#ifdef VXWORKS
	static _RETURNCODE_T CheckRemoteParticipant(ParticipantDataManager *pManager);
#else
	static DWORD WINAPI CheckRemoteParticipant(LPVOID lpManager);
#endif

    //�Ƴ����ڵ�Participant
    _RETURNCODE_T RemoveExpiredParticipant();

    //�Ƴ��˳���Participant
    _RETURNCODE_T RemoveLogoffParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //����
    _PARTICIPANT_DATALIST_T::iterator LookupRemoteParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //����
    _RETURNCODE_T AddRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);
    //ɾ��
    _RETURNCODE_T RemoveRemoteParticipant(_PARTICIPANT_DATALIST_T::iterator itData);
    //����
    _RETURNCODE_T RefreshRemoteParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pOriginal,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pLatest);
    //����
    _RETURNCODE_T RefreshRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pLatest);

private:
    //���ڵ�DomainParticipant
    DomainParticipant *m_pDomainParticipant;
    //Զ��Participant��Ϣ����
    _PARTICIPANT_DATALIST_T m_pRemoteParticipantList;

    //�ж��Ƿ���ͬһ��Participant
    bool IsSameParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData1,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData2);

    //������
#ifdef VXWORKS
	SEM_ID m_hSemMutex;
#else 
	HANDLE m_hSemMutex;
#endif
};

#endif
