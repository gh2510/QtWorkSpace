/************************************************************
** �ļ�����KeyedStringTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����KeyedStringTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRINGTYPESUPPORT_H_INCLUDED_
#define _DDS_KEYEDSTRINGTYPESUPPORT_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/TypeSupport.h"
class DomainParticipant;

class KeyedStringTypeSupport : public TypeSupport
{
public:
    //ע��_DDS_STRING����
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName);

    //��ȡTypeSupport���������������
    //static string Get_Type_Name() {
    //    return "_DDS_STRING";
    //}

    static char *Get_Type_Name()
    {
        return "KeyedString";
    }
};

#endif
