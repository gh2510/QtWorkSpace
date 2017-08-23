/************************************************************
** 文件名：DomainParticipantFactory.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-17
** 修改人：无
** 日  期：无
** 描  述：DomainParticipantFactory头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_
#define _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#ifdef VXWORKS  //移植
 #include <semLib.h>
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

class DomainParticipant;


class DomainParticipantFactory 
{
private:
    static DomainParticipantFactory* m_pInstance;
    //域参与者列表
    _DOMAIN_PARTICIPANT_MAP m_DomainParticipantMap;

    //构造函数
    DomainParticipantFactory();

    //析构函数
    virtual ~DomainParticipantFactory();

	//互斥锁
#ifdef VXWORKS          //移植修改
    static SEM_ID m_hSemMutex;
#elif WIN32
	 static HANDLE m_hSemMutex;
#elif KYLIN
public:
	 static pthread_mutex_t m_hSemMutex;
#endif


public:
    //返回DomainParticipantFactory对象指针
    static DomainParticipantFactory* Get_Instance();

    //创建域参与者
    DomainParticipant* Create_Participant(_DOMAINID_T DomainId, char* pCompName);

    //删除域参与者
    _RETURNCODE_T Delete_Participant(DomainParticipant* pDomainParticipant);

    //查找域参与者
    _DOMAIN_PARTICIPANT_LIST* Lookup_Participant(_DOMAINID_T DomainId);
};

#endif
