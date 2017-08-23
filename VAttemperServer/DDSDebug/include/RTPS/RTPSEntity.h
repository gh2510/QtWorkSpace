/************************************************************
** �ļ�����RTPSEntity.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-10
** �޸��ˣ���
** ��  �ڣ���
** ��  ����RTPSEntityͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_RTPSENTITY_H_INCLUDED_
#define _RTPS_RTPSENTITY_H_INCLUDED_

#include "BasicTypes.h"

class RTPSEntity 
{
public:
    RTPSEntity ( _GUID_T AGuid ) 
    {
        m_Guid = AGuid;
    }

    virtual ~RTPSEntity () 
    {
    };

    //����GUID
    _GUID_T Guid () 
    {
        return m_Guid;
    }
    //����_ENTITYID
    _ENTITY_ID_T EntityId () 
    {
        return m_Guid.EntityId;
    }

private:
    //GUID
    _GUID_T m_Guid;
};

#endif
