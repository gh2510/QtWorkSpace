/************************************************************
** 文件名：KeyedStringTypeSupport.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-20
** 修改人：无
** 日  期：无
** 描  述：KeyedStringTypeSupport头文件
** 版  本：Version 0.1
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
    //注册_DDS_STRING类型
    static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName);

    //获取TypeSupport代表的数据类型名
    //static string Get_Type_Name() {
    //    return "_DDS_STRING";
    //}

    const static char *Get_Type_Name()
    {
        return "KeyedString";
    }
};

#endif
