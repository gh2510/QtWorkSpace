/************************************************************
** 文件名：TransmitterMulticast.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-25
** 修改人：无
** 日  期：无
** 描  述：TransmitterMulticast头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_TRANSMITTERMULTICAST_H_INCLUDED_
#define _RTPS_TRANSMITTERMULTICAST_H_INCLUDED_

#include "BasicTypes.h"
#include "rtps/MessageTransmitter.h"

#ifndef VXWORKS   //移植
#pragma comment(lib,"ws2_32.lib") 
#include <winsock.h>
#endif

typedef map<_SOCKET_T, unsigned long> _MULTIADDRMAP_T;
//接收报文的最大长度 基于UDP
#ifdef VXWORKS
#define MAXSIZE 65536
#else
#define MAXSIZE 65536
#endif

class TransmitterMulticast : public MessageTransmitter 
{
public:
    //构造函数
    TransmitterMulticast(ReceiveBuffer *pReceiveBuffer);

    //析构函数
    virtual ~TransmitterMulticast();

    //利用Socket API 发送报文
    _RETURNCODE_T SendMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength);

    //利用Socket API 发送多播报文
    _RETURNCODE_T SendMultiMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength);
        
    //利用Socket API接收报文
    _RETURNCODE_T ReceiveMessage();
    
    //添加监听地址
    _RETURNCODE_T ReceiveAddrAdd(_LOCATOR_T ReceiveAddr);

    //添加监听多播地址
    _RETURNCODE_T ReceiveMultiAddrAdd(_LOCATOR_T SourceAddr, _LOCATOR_T ReceiveAddr);
    
    //删除监听地址
    _RETURNCODE_T ReceiveAddrRemove(_LOCATOR_T ReceiveAddr);

private:
    //接收报文
    char *m_pMsgBuffer;

    //发送socket
    _SEND_SOCKET_LIST m_SendSocket;

    //socket 绑定本地的IP和Port 需要循环监听
    _SOCKET_LIST_T m_ReceiveSocket;

    //监听的socket最大值 用于select方法中
    _SOCKET_T m_SocketMax;

    //监听的socket集合 用于select方法
    fd_set m_ReadSet;

	//2013-10-16 hjy modify发布订阅匹配时延，刚开始监听255.255.255.255的socket时间更长一点 
	int m_MatchTime;
    //
    _MULTIADDRMAP_T m_MultiAddrMap;
};

#endif
