/************************************************************
** �ļ�����StringTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-16
** �޸��ˣ���
** ��  �ڣ���
** ��  ����StringTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_STRINGTYPESUPPORT_H_INCLUDED_
#define _DDS_STRINGTYPESUPPORT_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/TypeSupport.h"
class DomainParticipant;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class StringTypeSupport : public TypeSupport
{
#else
class DDS_DLL StringTypeSupport : public TypeSupport
{
#endif
public:
    //ע��_DDS_STRING����
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName);

    //��ȡTypeSupport���������������
    //static string Get_Type_Name() {
    //    return "_DDS_STRING";
    //}

    static char *Get_Type_Name()
    {
        return "_DDS_STRING";
    }
};

#endif
