/************************************************************
** 文件名：ParticipantTypeSupport.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：ParticipantTypeSupport头文件
** 版  本：Version 0.1
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
