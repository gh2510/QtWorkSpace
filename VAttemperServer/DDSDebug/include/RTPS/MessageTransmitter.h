/************************************************************
** 文件名：MessageTransmitter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-16
** 修改人：无
** 日  期：无
** 描  述：MessageTransmitter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_MESSAGETRANSMITTER_H_INCLUDED_
#define _RTPS_MESSAGETRANSMITTER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifndef VXWORKS
#include "Windows.h"
#else
#include "semLib.h"
#endif

//声明
class ReceiveBuffer;

class MessageTransmitter 
{
public:
    //构造函数
    MessageTransmitter(ReceiveBuffer *pReceiveBuffer) 
    {
        m_pReceiveBuffer = pReceiveBuffer;

		//2013-10-15 hjy modify mutex修改
#ifdef VXWORKS
		memset(&m_hSemMutex, 0, sizeof(SEM_ID));	
		m_hSemMutex = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
#else
		m_hSemMutex = CreateMutex(NULL,FALSE,NULL);
#endif	
    }

    //析构函数
    virtual ~MessageTransmitter() 
    {
        m_Locator.clear();
    };

    //发送 虚函数提供接口
    virtual _RETURNCODE_T SendMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength) = 0;

    //多播发送 虚函数提供接口
    virtual _RETURNCODE_T SendMultiMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength) = 0;

    //接收 虚函数提供接口
    virtual _RETURNCODE_T ReceiveMessage() = 0;

    //添加监听地址
    virtual _RETURNCODE_T ReceiveAddrAdd(_LOCATOR_T ReceiveAddr) = 0;

    //添加监听多播地址
    virtual _RETURNCODE_T ReceiveMultiAddrAdd(_LOCATOR_T sourceAddr, _LOCATOR_T ReceiveAddr) = 0;

    //删除监听地址
    virtual _RETURNCODE_T ReceiveAddrRemove(_LOCATOR_T ReceiveAddr) = 0;

    //开始传输线程/任务
#ifdef VXWORKS   //移植
    static _RETURNCODE_T TransmitRun(MessageTransmitter *pMessageTransmitter);
#else
	static DWORD WINAPI TransmitRun(LPVOID lpMessageTransmitter);
#endif

protected:
    //接收缓冲区
    ReceiveBuffer *m_pReceiveBuffer;

    //监听地址列表
    _LOCATOR_LIST_T m_Locator;

	//用于互斥访问m_sendsocket
	//2013-10-15 hjy modify mutex修改
#ifdef VXWORKS
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
