/************************************************************
** 文件名：ParticipantDataManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：ParticipantDataManager头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_PARTICIPANTDATAMANAGER_H_INCLUDED_
#define _RTPS_PARTICIPANTDATAMANAGER_H_INCLUDED_

#ifdef VXWORKS  //移植
#include <semLib.h>
#elif WIN32
#pragma comment(lib,"ws2_32.lib") 
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#include <unistd.h>
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

    //判断是否是新的Participant
    bool IsNewParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //配置内置端点的Proxy
    _RETURNCODE_T BuiltinEntityProxyConfigure(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //删除内置端点的Proxy
    _RETURNCODE_T BuiltinEntityProxyRemove(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //删除用户端点的Proxy
    _RETURNCODE_T UserEntityProxyRemove(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //检查Participant是否过期 线程入口地址
#ifdef VXWORKS
	static _RETURNCODE_T CheckRemoteParticipant(ParticipantDataManager *pManager);
#elif WIN32
	static DWORD WINAPI CheckRemoteParticipant(LPVOID lpManager);
#elif KYLIN
	static void* CheckRemoteParticipant(void *pManager);
#endif

    //移除过期的Participant
    _RETURNCODE_T RemoveExpiredParticipant();

    //移除退出的Participant
    _RETURNCODE_T RemoveLogoffParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA* pData);

    //查找
    _PARTICIPANT_DATALIST_T::iterator LookupRemoteParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //增加
    _RETURNCODE_T AddRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteParticipant(_PARTICIPANT_DATALIST_T::iterator itData);
    //更新
    _RETURNCODE_T RefreshRemoteParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pOriginal,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pLatest);
    //更新
    _RETURNCODE_T RefreshRemoteParticipant(_SPDP_DISCOVERED_PARTICIPANT_DATA *pLatest);

private:
    //属于的DomainParticipant
    DomainParticipant *m_pDomainParticipant;
    //远端Participant信息链表
    _PARTICIPANT_DATALIST_T m_pRemoteParticipantList;

    //判断是否是同一个Participant
    bool IsSameParticipant(
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData1,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pData2);

    //互斥锁
#ifdef VXWORKS
	SEM_ID m_hSemMutex;
#elif WIN32 
	HANDLE m_hSemMutex;
#elif KYLIN
	pthread_mutex_t m_hSemMutex;
	int _sem_init_ret;
#endif
};

#endif
