/************************************************************
** �ļ�����LocalDataGatherer.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����LocalDataGathererͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_LOCALDATAGATHERER_H_INCLUDE_
#define _RTPS_LOCALDATAGATHERER_H_INCLUDE_

#include "BasicTypes.h"
#include "ReturnCode.h"

class LocalDataGatherer 
{
public:
    //��ȡ����DomainParticipant��Ϣ
    static _SPDP_DISCOVERED_PARTICIPANT_DATA* ObtainSPDPdiscoveredParticipantData(
        DomainParticipant *pDomainParticipant,
        _DURATION_T LeaseTime,
        _ENTITY_STATUS_T ParticipantStatus);

    //��ȡDataWriter����Ϣ
    static _DISCOVERED_WRITER_DATA* ObtainDiscoveredWriterData(
        DataWriter* pDataWriter,
        _ENTITY_STATUS_T WriterStatus);

    //��ȡDataReader����Ϣ
    static _DISCOVERED_READER_DATA* ObtainDiscoveredReaderData(
        DataReader* pDataReader,
        _ENTITY_STATUS_T pReaderStatus);
};

#endif
