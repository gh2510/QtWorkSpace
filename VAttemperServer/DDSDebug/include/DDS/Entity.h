/************************************************************
** �ļ�����Entity.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-17
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Entityͷ�ļ�
** ��  ����Version 0.1
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
    //QoS����
    _ENTITY_QOS* m_pQos;
    //������ָ��
    DDSListener* m_pListener;

public:
    Entity() {};
    virtual ~Entity() {};

    //����QoS����
    virtual _RETURNCODE_T SetQos(_ENTITY_QOS* pQos) 
    {
        m_pQos = pQos;
        return RETURNCODE_OK;
    }
    //��ȡQoS����
    //virtual _ENTITY_QOS* GetQos() {
    //    return m_pQos;
    //}
    ////���ü�����
    //virtual _RETURNCODE_T SetListener(DDSListener *pListener, _STATUS_MASK Mask) = 0;
    ////��ȡ������
    //virtual DDSListener* GetListener() = 0;
};

#endif
