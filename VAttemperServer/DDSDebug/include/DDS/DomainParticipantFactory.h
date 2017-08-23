/************************************************************
** �ļ�����DomainParticipantFactory.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-17
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DomainParticipantFactoryͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_
#define _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#include "Windows.h"
#endif

class DomainParticipant;


class DomainParticipantFactory 
{
private:
    static DomainParticipantFactory* m_pInstance;
    //��������б�
    _DOMAIN_PARTICIPANT_MAP m_DomainParticipantMap;

    //���캯��
    DomainParticipantFactory();

    //��������
    virtual ~DomainParticipantFactory();

	//������
#ifdef VXWORKS          //��ֲ�޸�
    static SEM_ID m_hSemMutex;
#else
	 static HANDLE m_hSemMutex;
#endif


public:
    //����DomainParticipantFactory����ָ��
    static DomainParticipantFactory* Get_Instance();

    //�����������
    DomainParticipant* Create_Participant(_DOMAINID_T DomainId, char* pCompName);

    //ɾ���������
    _RETURNCODE_T Delete_Participant(DomainParticipant* pDomainParticipant);

    //�����������
    _DOMAIN_PARTICIPANT_LIST* Lookup_Participant(_DOMAINID_T DomainId);
};

#endif
