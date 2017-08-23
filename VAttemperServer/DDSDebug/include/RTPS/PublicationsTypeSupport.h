/************************************************************
** �ļ�����ParticipantTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ParticipantTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_PublicationsTYPESUPPORT_H_INCLUDED_ 
#define _DDS_PublicationsTYPESUPPORT_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
#include "rtps/PublicationsAgent.h"
class DomainParticipant;

class PublicationsTypeSupport : public TypeSupport 
{
public:
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName) 
    {
        Agent *pNewAgent = NULL;
        try 
        {
            pNewAgent = new PublicationsAgent(pDomainParticipant, strTypeName);
        }
        catch (_RETURNCODE_T &Ret) 
        { 
            if (Ret == RETURNCODE_REGISTER_TYPE_EXISTED) 
            { 
                delete pNewAgent; 
            } 
        }
        return RETURNCODE_OK;
    }

    static string Get_Type_Name() 
    { 
        return "Publications";
    }
};

#endif
