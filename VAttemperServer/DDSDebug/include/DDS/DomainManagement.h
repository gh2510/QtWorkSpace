/************************************************************
** 文件名：DomainManagement.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-20
** 修改人：无
** 日  期：无
** 描  述：DomainManagement头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_DOMAINMANAGEMENT_H_INCLUDED_
#define _API_DOMAINMANAGEMENT_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
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
	//互斥锁
#ifdef VXWORKS   //移植
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif
};

#endif
