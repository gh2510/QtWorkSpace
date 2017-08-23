/************************************************************
** 文件名：LocalDataGatherer.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-13
** 修改人：无
** 日  期：无
** 描  述：LocalDataGatherer头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_LOCALDATAGATHERER_H_INCLUDE_
#define _RTPS_LOCALDATAGATHERER_H_INCLUDE_

#include "BasicTypes.h"
#include "ReturnCode.h"

class LocalDataGatherer 
{
public:
    //获取本地DomainParticipant信息
    static _SPDP_DISCOVERED_PARTICIPANT_DATA* ObtainSPDPdiscoveredParticipantData(
        DomainParticipant *pDomainParticipant,
        _DURATION_T LeaseTime,
        _ENTITY_STATUS_T ParticipantStatus);

    //获取DataWriter的信息
    static _DISCOVERED_WRITER_DATA* ObtainDiscoveredWriterData(
        DataWriter* pDataWriter,
        _ENTITY_STATUS_T WriterStatus);

    //获取DataReader的信息
    static _DISCOVERED_READER_DATA* ObtainDiscoveredReaderData(
        DataReader* pDataReader,
        _ENTITY_STATUS_T pReaderStatus);
};

#endif
