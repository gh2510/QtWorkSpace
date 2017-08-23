/************************************************************
** 文件名：KeyedString.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-20
** 修改人：无
** 日  期：无
** 描  述：KeyedString头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRING_H_INCLUDED_
#define _DDS_KEYEDSTRING_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/CDR.h"
#include "dds/MD5.h"

struct KEYED_STRING
{
    char* pKey;
    char* pValue;

    //构造函数
    KEYED_STRING();
    KEYED_STRING(int iKey_size, int iSize);
    KEYED_STRING(const KEYED_STRING& KeyedString);
    KEYED_STRING& operator= (const KEYED_STRING& KeyedString);
    //析构函数
    ~KEYED_STRING();

    //串化
    void Marshal(CDR *pCdr) const;

    //反串化
    void UnMarshal(CDR *pCdr);
};

typedef struct KEYED_STRING _KEYED_STRING_KEY_HOLDER;
typedef vector<KEYED_STRING> _KEYED_STRING_SEQ;
typedef map<_INSTANCE_HANDLE_T, _KEYED_STRING_KEY_HOLDER> _INSTANCE_HANDLE_TO_KEY_HOLDER;

//将sample中的key值串化到stream中,stream是key串
bool KeyedString_serialize_key(const KEYED_STRING* pSample, CDR* pStream);

//将stream中key值反串化到sample中,stream是key串
//bool KeyedString_deserialize_key_sample(KEYED_STRING* pSample, CDR* pStream);

//将stream中key值反串化到sample中,stream是串化的sample
//bool KeyedString_serialized_sample_to_key(KEYED_STRING* pSample, CDR* pStream);

//把instance的key值拷贝到keyHolder中
bool KeyedString_instance_to_key(_KEYED_STRING_KEY_HOLDER* pKeyHolder, const KEYED_STRING* pInstance);

//把keyHolder中的key值拷贝到instance中
//bool KeyedString_key_to_instance(KEYED_STRING* instance, const _KEYED_STRING_KEY_HOLDER* keyHolder);

//计算instance的keyhash
bool KeyedString_instance_to_keyhash(_KEY_HASH_T* pKeyhash, const KEYED_STRING* pInstance);

//计算stream串的keyhash
//bool KeyedString_serialized_sample_to_keyhash(CDR* pStream, _KEY_HASH_T* keyhash);


#endif
