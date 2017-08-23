/************************************************************
** 文件名：DomainEntity.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：DomainEntity头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DOMAINENTITY_H_INCLUDED_
#define _DDS_DOMAINENTITY_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "Entity.h"

#define DEF_NARROW_METHOD(TYPE) \
    static int type_id(); \
    virtual void *narrow_helper(long type_const)

#define IMPL_NARROW_METHOD(TYPE)\
    int \
    TYPE::type_id()\
{\
    return 0;\
}\
    void * \
    TYPE::narrow_helper(long type_const) {\
    void *rval = NULL; \
    if (type_const == (long)&TYPE::type_id) \
    rval = this; \
    return rval; \
}

//typedef unsigned long _STATUS_MASK;
/***********************************************************************/
#if defined(VXWORKS) || defined(_DDS_LIB_FILE) || defined(KYLIN)
class DomainEntity : public Entity {
#else
class DDS_DLL DomainEntity : public Entity 
{
#endif
public:
    DomainEntity(){}
    virtual ~DomainEntity(){}
};

#endif
