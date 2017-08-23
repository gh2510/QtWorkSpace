/************************************************************
** 文件名：StringTypeSupport.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-16
** 修改人：无
** 日  期：无
** 描  述：StringTypeSupport头文件
** 版  本：Version 0.1
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
    //注册_DDS_STRING类型
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName);

    //获取TypeSupport代表的数据类型名
    //static string Get_Type_Name() {
    //    return "_DDS_STRING";
    //}

    static char *Get_Type_Name()
    {
        return "_DDS_STRING";
    }
};

#endif
