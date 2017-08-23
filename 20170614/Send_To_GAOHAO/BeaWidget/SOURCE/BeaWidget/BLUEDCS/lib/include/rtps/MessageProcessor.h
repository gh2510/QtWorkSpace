/************************************************************
** 文件名：MessageProcessor.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-13
** 修改人：无
** 日  期：无
** 描  述：MessageProcessor头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_MESSAGEPROCESSOR_H_INCLUDED_
#define _RTPS_MESSAGEPROCESSOR_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Message.h"


#ifdef KYLIN
#include <unistd.h>
#endif

//声明
class Participant;
class MessageTransmitter;
class ReceiveBuffer;

class MessageProcessor 
{
public:
    //构造函数
    MessageProcessor(
        Participant *pParticipant,
        ReceiveBuffer *pBuffer,
        MessageTransmitter *pMessageTransmitter);

    //析构函数
    virtual ~MessageProcessor(){};

    //封装报文
    char *EncapsulateMessage(char *pMessage, unsigned long *ulLength);

    //解析报文
    _RETURNCODE_T InterpretMessage();

    //处理任务/线程 入口函数
#ifdef VXWORKS   //移植
    static _RETURNCODE_T ProcessRun(MessageProcessor *messageProcessor);
#elif WIN32
	static DWORD WINAPI ProcessRun(LPVOID messageProcessor);
#elif KYLIN
	static void* ProcessRun(void*messageProcessor);
#endif

    Participant *GetParticipant() 
    {
        return m_pRelatedParticipant;
    }

private:
    //解析报文头
    _RETURNCODE_T InterpretMessageHeader(_RECEIVER *pReceiver);

    //解析子报文
    _RETURNCODE_T InterpretSubmessage(_RECEIVER *pReceiver);

    //解析Data子报文
    _RETURNCODE_T InterpretDataMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

	//解析DataFrag子报文
	_RETURNCODE_T InterpretDataFragMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

    //解析Heartbeat子报文
    _RETURNCODE_T InterpretHeartbeatMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

    //解析AckNack子报文
    _RETURNCODE_T InterpretAckNackMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

	//解析AckNack子报文
    _RETURNCODE_T InterpretNackFragMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

private:
    //对应的Participant
    Participant *m_pRelatedParticipant;

    //报文传输端
    MessageTransmitter *m_pMessageTransmitter;

    //接收缓冲区
    ReceiveBuffer *m_pReceiveBuffer;
};

#endif
