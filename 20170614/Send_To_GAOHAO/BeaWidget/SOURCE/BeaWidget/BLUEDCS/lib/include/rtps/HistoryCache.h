/************************************************************
** 文件名：HistoryCache.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：HistoryCache头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _CACHE_HISTORYCACHE_H_INCLUDED_
#define _CACHE_HISTORYCACHE_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
//移植
#ifdef VXWORKS      
 #include <semLib.h> 
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

class HistoryCache 
{
public:
    HistoryCache(unsigned long ulLength);
    virtual ~HistoryCache();

    //写入
    _RETURNCODE_T AddChange(_CACHE_CHANGE *W_CacheChange);
    //删除
    _RETURNCODE_T RemoveChange(_SEQUENCE_NUMBER_T SeqNum);
    //读出
    _CACHE_CHANGE *GetChange(_SEQUENCE_NUMBER_T SeqNum);

    //获取缓冲区中数据序列号最小值
    _SEQUENCE_NUMBER_T GetSeqNumMin();
    //获取缓冲区中数据序列号最大值
    _SEQUENCE_NUMBER_T GetSeqNumMax();

    //获取缓冲区状态序号
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

    //检查缓冲区是否为满
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


    //检查缓冲区是否为空
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


    //检查数据是否存在于缓冲区中
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
    //缓冲区的大小
    unsigned long m_ulCacheLength;
    //缓冲区当前包含的_CACHE_CHANGE的个数
    unsigned long m_ulCacheNum;
    //下一次添加数据的起始位置
    unsigned long m_ulPositionAdd;
    //缓冲区的状态序号
    _COUNT_T m_StatusCount;
    //缓冲区中数据序列号（SequenceNumber）的索引
    _INDEX_T m_Index;
    //存放_CACHE_CHANGE的空间
    _CACHE_CHANGE **m_Changes;

    //互斥锁
#ifdef VXWORKS       //移植
	SEM_ID m_hSemMutex;
#elif WIN32
	HANDLE m_hSemMutex;
#elif KYLIN
	pthread_mutex_t m_hSemMutex;
#endif

    //计数器信号量 表示HistoryCache中_CACHE_CHANGE的个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemFull;
#elif WIN32
	HANDLE m_hSemFull;
#elif KYLIN
	sem_t m_hSemFull;
#endif

    //计数器信号量 表示HistoryCache中仍剩余的空间个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemEmpty;
#elif WIN32
	HANDLE m_hSemEmpty;
#elif KYLIN
	sem_t m_hSemEmpty;
	int _sem_init_ret;
#endif
};

#endif
