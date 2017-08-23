/************************************************************
** 文件名：Entity.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-17
** 修改人：无
** 日  期：无
** 描  述：Entity头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_ENTITY_H_INCLUDED_
#define _DDS_ENTITY_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"

class DDSListener;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class Entity {
#else
class DDS_DLL Entity 
{
#endif
protected:
    //QoS设置
    _ENTITY_QOS* m_pQos;
    //监听器指针
    DDSListener* m_pListener;

public:
    Entity() {};
    virtual ~Entity() {};

    //设置QoS策略
    virtual _RETURNCODE_T SetQos(_ENTITY_QOS* pQos) 
    {
        m_pQos = pQos;
        return RETURNCODE_OK;
    }
    //获取QoS策略
    //virtual _ENTITY_QOS* GetQos() {
    //    return m_pQos;
    //}
    ////设置监听器
    //virtual _RETURNCODE_T SetListener(DDSListener *pListener, _STATUS_MASK Mask) = 0;
    ////获取监听器
    //virtual DDSListener* GetListener() = 0;
};

#endif
