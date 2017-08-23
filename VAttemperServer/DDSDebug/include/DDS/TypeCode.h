/************************************************************
** 文件名：TypeCode.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-07-02
** 修改人：无
** 日  期：无
** 描  述：TypeCode头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef TYPECODE_H
#define TYPECODE_H

#include "BasicTypes.h"

enum _TC_KIND 
{
    tk_null		= 0,
    tk_void		= 1,
    tk_short	= 2,
    tk_long		= 3,
    tk_ushort	= 4,
    tk_ulong	= 5,
    tk_float	= 6,
    tk_double	= 7,
    tk_boolean	= 8,
    tk_char		= 9,
    tk_octet	= 10,
    tk_any		= 11,
    tk_TypeCode	= 12,
    tk_Principal= 13,
    tk_objref	= 14,
    tk_struct	= 15,
    tk_union	= 16,
    tk_enum		= 17,
    tk_string	= 18,
    tk_sequence	= 19,
    tk_array	= 20,
    tk_alias	= 21,		
    tk_except	= 22,

    // these five are OMG-IDL pData type extensions
    tk_longlong	= 23,		
    tk_ulonglong	= 24,	
    tk_longdouble	= 25,
    tk_wchar	= 26,
    tk_wstring	= 27,

    tk_NamedValue   = 28,
    tk_NVList       = 29,
    tk_Context      = 30,
    tk_ContextList  = 31,

    //keyed type
    tk_keyedvoid		= 32,
    tk_keyedshort	= 33,
    tk_keyedlong		= 34,
    tk_keyedushort	= 35,
    tk_keyedulong	= 36,
    tk_keyedfloat	= 37,
    tk_keyeddouble	= 38,
    tk_keyedboolean	= 39,
    tk_keyedchar		= 40,
    tk_keyedoctet	= 41,
    tk_keyedany		= 42,
    tk_keyedTypeCode	= 43,
    tk_keyedPrincipal= 44,
    tk_keyedobjref	= 45,
    tk_keyedstruct	= 46,
    tk_keyedunion	= 47,
    tk_keyedenum		= 48,
    tk_keyedstring	= 49,
    tk_keyedsequence	= 50,
    tk_keyedarray	= 51,
    tk_keyedalias	= 52,		
    tk_keyedexcept	= 53,

    // these five are OMG-IDL pData type extensions
    tk_keyedlonglong	= 54,		
    tk_keyedulonglong	= 55,	
    tk_keyedlongdouble	= 56,
    tk_keyedwchar	= 57,
    tk_keyedwstring	= 58,

    tk_keyedNamedValue   = 59,
    tk_keyedNVList       = 60,
    tk_keyedContext      = 61,
    tk_keyedContextList  = 62,

    TC_KIND_COUNT
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class TypeCode
#else
class DDS_DLL TypeCode
#endif
{
    //unsigned    _refcount;   // reference count of the typecode
    //Boolean     _orb_owns;   // whether orb owns the typecode

public :
    unsigned long		m_ulLength;     // ulLength of typecode object
    unsigned char		*m_pBuffer;    // CDR format typecode content
    _TC_KIND            m_Kind;       // typecode Kind
    //_TYPE_CODE_PTR      _parent;     // its parent typecode

    TypeCode(_TC_KIND Kind);        //TypeCode.h
    TypeCode(_TC_KIND Kind, unsigned long ulLength, Octet *pBuffer);//TypeCode.h
    //TypeCode(const TypeCode &tc);
    TypeCode();
    ~TypeCode();
    TypeCode  &operator= (const TypeCode &Tc);//TypeCode.h

    // CORBA 2.0 operations

    //Boolean equal(TypeCode *tc, Environment &env = default_env());
    _TC_KIND  Kind() const;

    //char* id () const;
    char *Name () const;

    unsigned long member_count() const;     //TypeCode.h
    char *member_name(unsigned long N) const;   //TypeCode.h

    _TYPE_CODE_PTR member_type(unsigned long N) const;//TypeCode.h

    //Any_ptr      member_label (ULong index, Environment &env = default_env()) const;
    //_TYPE_CODE_PTR discriminator_type(Environment &env = default_env()) const;
    //Long         default_index(Environment &env = default_env()) const;

    unsigned long ulLength() const;//TypeCode.h

    _TYPE_CODE_PTR content_type() const;//TypeCode.h

    //ULong	  param_count (Environment &env = default_env()) const;
    // The parameter(Long N) function will not be implemented in ORBUS
    //
    //Any_ptr parameter(Long N, Environment &env = default_env()) const;

    static _TYPE_CODE_PTR	_duplicate (_TYPE_CODE_PTR Tc)//TypeCode.h
    {
        //if (tc->orb_owns() == TRUE) 
        //  tc->refcount(tc->refcount() + 1); 
        return Tc;
    }

    // Orbus specific operations
    //ULong	ulong_param (ULong N, Environment &env =
    //                           default_env()) const;
    //_TYPE_CODE_PTR	typecode_param (ULong N, Environment &env =
    //                              default_env()) const;

    enum TRAVERSE_STATUS { TRAVERSE_STOP, TRAVERSE_CONTINUE };//TypeCode.h

    typedef TRAVERSE_STATUS (* VisitRoutine)(_TYPE_CODE_PTR Tc,
        const void *pValue1, const void *pValue2, void *pContext);//TypeCode.h

    TRAVERSE_STATUS  Traverse(const void *pValue1, const void *pValue2,
        VisitRoutine Visit, void *pContext);//TypeCode.h

    unsigned int size (bool bEncoder);//TypeCode.h
    //size_t alignment (Environment &env = default_env());

    //unsigned refcount() const { return _refcount; }
    //void refcount(unsigned ref) { _refcount = ref; }  
    //Boolean orb_owns() const { return _orb_owns; }
};
#endif
