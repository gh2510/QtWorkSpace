/************************************************************
** 文件名：RTPSEntity.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-10
** 修改人：无
** 日  期：无
** 描  述：RTPSEntity头文件
** 版  本：Version 0.1
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

    //返回GUID
    _GUID_T Guid () 
    {
        return m_Guid;
    }
    //返回_ENTITYID
    _ENTITY_ID_T EntityId () 
    {
        return m_Guid.EntityId;
    }

private:
    //GUID
    _GUID_T m_Guid;
};

#endif
