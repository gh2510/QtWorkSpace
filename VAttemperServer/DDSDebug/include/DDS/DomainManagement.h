/************************************************************
** �ļ�����DomainManagement.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DomainManagementͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_DOMAINMANAGEMENT_H_INCLUDED_
#define _API_DOMAINMANAGEMENT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#include "Windows.h"
#endif

class DomainParticipant;

struct _DOMAIN_RECORD 
{
    _DOMAINID_T DomainId;
    DomainParticipant *pDomainParticipant;
    unsigned long ulCount;
    _DOMAIN_RECORD *pNextDomainRecord;
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DomainManagement 
{
#else
class DDS_DLL DomainManagement 
{
#endif
public:
    static DomainManagement *GetInstance();
    DomainParticipant *DomainInit(_DOMAINID_T DomainId, char* pCompName);
    DomainParticipant *ParticipantGet(_DOMAINID_T DomainId);
    _RETURNCODE_T DomainRelease(_DOMAINID_T DomainId);

private:
    static DomainManagement *m_pInstance;
    _DOMAIN_RECORD *m_pDomainRecord;
    DomainManagement () 
    {
        m_pDomainRecord = NULL;
    };

	~DomainManagement () 
	{
		m_pDomainRecord = NULL;
	};
	//������
#ifdef VXWORKS   //��ֲ
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
