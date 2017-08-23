/************************************************************
** 文件名：ReceiveBuffer.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-16
** 修改人：无
** 日  期：无
** 描  述：ReceiveBuffer头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_RECEIVEBUFFER_H_INCLUDED_
#define _RTPS_RECEIVEBUFFER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //移植
#include <semLib.h>
#elif WIN32
#include "Windows.h"
#elif KYLIN
#include <semaphore.h>
#endif

class ReceiveBuffer 
{
public:
    //构造函数
    ReceiveBuffer(unsigned long ulLength);

    //析构函数
    virtual ~ReceiveBuffer();

    //读
    _RETURNCODE_T Read(char *pMessage, unsigned long ulLength);

    //写
    _RETURNCODE_T Write(char *pMessage, unsigned long ulLength, unsigned long ulAddress);

	//将读指针指到填充字段之后
    _RETURNCODE_T FindPad();

private:
    //缓冲区大小
    unsigned long m_ulLength;

    //读指针位置
    unsigned long m_ulReadPosition;

    //写指针位置
    unsigned long m_ulWritePosition;

    //缓冲区 一个循环的空间
    char *m_pBuffer;

	//现有可写空间
	unsigned long m_ulAvailableLength;

    //互斥信号量
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#elif WIN32
	HANDLE m_hSemMutex;
#elif KYLIN
	pthread_mutex_t m_hSemMutex;
#endif

    //计数器信号量 表示缓冲区中写入的数据个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemFull;
#elif WIN32
	HANDLE m_hSemFull;
#elif KYLIN
	pthread_mutex_t m_hSemFull;
#endif

    //计数器信号量 表示缓冲区中仍剩余的空间个数
#ifdef VXWORKS   //移植
	SEM_ID m_hSemEmpty;
#elif WIN32
	HANDLE m_hSemEmpty;
#elif KYLIN
	pthread_mutex_t m_hSemEmpty;
#endif
};

#endif
