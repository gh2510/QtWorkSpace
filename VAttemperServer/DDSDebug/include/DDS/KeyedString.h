/************************************************************
** �ļ�����KeyedString.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����KeyedStringͷ�ļ�
** ��  ����Version 0.1
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

    //���캯��
    KEYED_STRING();
    KEYED_STRING(int iKey_size, int iSize);
    KEYED_STRING(const KEYED_STRING& KeyedString);
    KEYED_STRING& operator= (const KEYED_STRING& KeyedString);
    //��������
    ~KEYED_STRING();

    //����
    void Marshal(CDR *pCdr) const;

    //������
    void UnMarshal(CDR *pCdr);
};

typedef struct KEYED_STRING _KEYED_STRING_KEY_HOLDER;
typedef vector<KEYED_STRING> _KEYED_STRING_SEQ;
typedef map<_INSTANCE_HANDLE_T, _KEYED_STRING_KEY_HOLDER> _INSTANCE_HANDLE_TO_KEY_HOLDER;

//��sample�е�keyֵ������stream��,stream��key��
bool KeyedString_serialize_key(const KEYED_STRING* pSample, CDR* pStream);

//��stream��keyֵ��������sample��,stream��key��
//bool KeyedString_deserialize_key_sample(KEYED_STRING* pSample, CDR* pStream);

//��stream��keyֵ��������sample��,stream�Ǵ�����sample
//bool KeyedString_serialized_sample_to_key(KEYED_STRING* pSample, CDR* pStream);

//��instance��keyֵ������keyHolder��
bool KeyedString_instance_to_key(_KEYED_STRING_KEY_HOLDER* pKeyHolder, const KEYED_STRING* pInstance);

//��keyHolder�е�keyֵ������instance��
//bool KeyedString_key_to_instance(KEYED_STRING* instance, const _KEYED_STRING_KEY_HOLDER* keyHolder);

//����instance��keyhash
bool KeyedString_instance_to_keyhash(_KEY_HASH_T* pKeyhash, const KEYED_STRING* pInstance);

//����stream����keyhash
//bool KeyedString_serialized_sample_to_keyhash(CDR* pStream, _KEY_HASH_T* keyhash);


#endif
