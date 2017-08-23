/************************************************************
** �ļ�����HistoryCache.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����HistoryCacheͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _CACHE_HISTORYCACHE_H_INCLUDED_
#define _CACHE_HISTORYCACHE_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
//��ֲ
#ifdef VXWORKS      
 #include <semLib.h> 
#else
#include "Windows.h"
#endif

class HistoryCache 
{
public:
    HistoryCache(unsigned long ulLength);
    virtual ~HistoryCache();

    //д��
    _RETURNCODE_T AddChange(_CACHE_CHANGE *W_CacheChange);
    //ɾ��
    _RETURNCODE_T RemoveChange(_SEQUENCE_NUMBER_T SeqNum);
    //����
    _CACHE_CHANGE *GetChange(_SEQUENCE_NUMBER_T SeqNum);

    //��ȡ���������������к���Сֵ
    _SEQUENCE_NUMBER_T GetSeqNumMin();
    //��ȡ���������������к����ֵ
    _SEQUENCE_NUMBER_T GetSeqNumMax();

    //��ȡ������״̬���
    _COUNT_T GetStatusCount() 
    {
        return m_StatusCount;
    }

    unsigned long GetNum()
    {
        return m_ulCacheNum;
    }

    unsigned long GetCacheLength() 
    {
        return m_ulCacheLength;
    }

private:

    //��黺�����Ƿ�Ϊ��
    bool Full() 
    {
        if (m_ulCacheNum >= m_ulCacheLength) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }


    //��黺�����Ƿ�Ϊ��
    bool Empty() 
    {
        if (m_ulCacheNum == 0) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }


    //��������Ƿ�����ڻ�������
    bool Exist(_SEQUENCE_NUMBER_T SeqNum) 
    {
        _INDEX_T::iterator it = m_Index.find(SeqNum);
        if (it == m_Index.end())
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

private:
    //�������Ĵ�С
    unsigned long m_ulCacheLength;
    //��������ǰ������_CACHE_CHANGE�ĸ���
    unsigned long m_ulCacheNum;
    //��һ��������ݵ���ʼλ��
    unsigned long m_ulPositionAdd;
    //��������״̬���
    _COUNT_T m_StatusCount;
    //���������������кţ�SequenceNumber��������
    _INDEX_T m_Index;
    //���_CACHE_CHANGE�Ŀռ�
    _CACHE_CHANGE **m_Changes;

    //������
#ifdef VXWORKS       //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

    //�������ź��� ��ʾHistoryCache��_CACHE_CHANGE�ĸ���
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemFull;
#else
	HANDLE m_hSemFull;
#endif

    //�������ź��� ��ʾHistoryCache����ʣ��Ŀռ����
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemEmpty;
#else
	HANDLE m_hSemEmpty;
#endif
};

#endif
