/************************************************************
** �ļ�����TypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����TypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TYPESUPPORT_H_INCLUDED_
#define _DDS_TYPESUPPORT_H_INCLUDED_

//#include <string>
//class DomainParticipant;

class DDS_DLL TypeSupport 
{
public:
    TypeSupport() {};
    virtual ~TypeSupport () {};
//
//    //ע���û��������������
//    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, char* typeName);
//
//    //��ȡTypeSupport���������������
//    static string Get_Type_Name();
};

#endif
