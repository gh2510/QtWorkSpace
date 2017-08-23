/************************************************************
** 文件名：PublicationsDataManager.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：PublicationsDataManager头文件
** 版  本：Version 0.1
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

    //判断是否是新的DataWriter
    bool IsNewDataWriter(_DISCOVERED_WRITER_DATA *pData);

    //配置WriterProxy
    //接收到一个远端DataWriter的新建信息，将其与本地所有的DataReader匹配，建立WriterProxy
    _RETURNCODE_T WriterProxyConfigure(
        _DISCOVERED_WRITER_DATA* pData);

    //配置WriterProxy
    //本地新建了一个DataReader，将其与所有远端的DataWriter信息匹配，建立WriterProxy
    _RETURNCODE_T WriterProxyConfigure(
        DataReader* pDataReader);

    //删除WriterProxy
    //接收到远端的DataWriter的删除信息，在本地所有DataReader的WriterProxy中寻找其信息，删除
    _RETURNCODE_T WriterProxyRemove(
        _DISCOVERED_WRITER_DATA* pData);

    //增加
    _RETURNCODE_T AddRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //删除
    _RETURNCODE_T RemoveRemoteDataWriter(_PUBLICATIONS_DATA_LIST_T::iterator itData);
    //更新
    _RETURNCODE_T RefreshRemoteDataWriter(_DISCOVERED_WRITER_DATA *pData);
    //更新
    _RETURNCODE_T RefreshRemoteDataWriter(
        _DISCOVERED_WRITER_DATA *pData1,
        _DISCOVERED_WRITER_DATA *pData2);

    //远端的Participant超时 删除其下所有DataWriter
    _RETURNCODE_T RemoteParticipantTimeout(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

	//返回远端发布信息列表
	_PUBLICATIONS_DATA_LIST_T RemotePublicationsList() 
    {
		return m_pRemotePublicationsList;
	}

private:
    //属于的DomainParticipant
    DomainParticipant *m_pDomainParticipant;

    //远端DataWriter信息链表
    _PUBLICATIONS_DATA_LIST_T m_pRemotePublicationsList;

    //查找
    _PUBLICATIONS_DATA_LIST_T::iterator LookupRemoteDataWriter(
        _DISCOVERED_WRITER_DATA *pData);

    //判断是否是同一个DataWriter
    bool IsSameDataWriter(
        _DISCOVERED_WRITER_DATA *pData1,
        _DISCOVERED_WRITER_DATA *pData2);

    //为DataReader做匹配 配置WriterProxy
    bool MatchDataReader(
        DataReader *pDataReader,
        _DISCOVERED_WRITER_DATA *pData);

    //判断DataWriter是否属于Participant
    bool Belong(_DISCOVERED_WRITER_DATA *pWriterData,
        _SPDP_DISCOVERED_PARTICIPANT_DATA *pParticipantData);
	bool Belong(_DISCOVERED_WRITER_DATA *pWriterData,
        Participant *aParticipant);


    //互斥锁
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
