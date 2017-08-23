//������
/************************************************************
** �ļ�����MassDataTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2013-07-22
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MassTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATATYPESUPPORT_H_INCLUDED_
#define _DDS_MASSDATATYPESUPPORT_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/TypeSupport.h"
class DomainParticipant;


class MassDataTypeSupport : public TypeSupport
{
public:
    //ע�����������
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName);

    //��ȡTypeSupport���������������
    //static string Get_Type_Name() {
    //    return "_DDS_STRING";
    //}

    static char *Get_Type_Name()
    {
        return "_MASS_DATA";
    }
};

#endif
