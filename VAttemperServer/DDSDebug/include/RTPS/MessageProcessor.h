/************************************************************
** �ļ�����MessageProcessor.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-13
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MessageProcessorͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_MESSAGEPROCESSOR_H_INCLUDED_
#define _RTPS_MESSAGEPROCESSOR_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Message.h"

//����
class Participant;
class MessageTransmitter;
class ReceiveBuffer;

class MessageProcessor 
{
public:
    //���캯��
    MessageProcessor(
        Participant *pParticipant,
        ReceiveBuffer *pBuffer,
        MessageTransmitter *pMessageTransmitter);

    //��������
    virtual ~MessageProcessor(){};

    //��װ����
    char *EncapsulateMessage(char *pMessage, unsigned long *ulLength);

    //��������
    _RETURNCODE_T InterpretMessage();

    //��������/�߳� ��ں���
#ifdef VXWORKS   //��ֲ
    static _RETURNCODE_T ProcessRun(MessageProcessor *messageProcessor);
#else
	static DWORD WINAPI ProcessRun(LPVOID messageProcessor);
#endif

    Participant *GetParticipant() 
    {
        return m_pRelatedParticipant;
    }

private:
    //��������ͷ
    _RETURNCODE_T InterpretMessageHeader(_RECEIVER *pReceiver);

    //�����ӱ���
    _RETURNCODE_T InterpretSubmessage(_RECEIVER *pReceiver);

    //����Data�ӱ���
    _RETURNCODE_T InterpretDataMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

	//����DataFrag�ӱ���
	_RETURNCODE_T InterpretDataFragMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

    //����Heartbeat�ӱ���
    _RETURNCODE_T InterpretHeartbeatMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

    //����AckNack�ӱ���
    _RETURNCODE_T InterpretAckNackMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

	//����AckNack�ӱ���
    _RETURNCODE_T InterpretNackFragMessage(_SUBMESSAGE_HEADER *pSubmessageHeader, _RECEIVER *pReceiver);

private:
    //��Ӧ��Participant
    Participant *m_pRelatedParticipant;

    //���Ĵ����
    MessageTransmitter *m_pMessageTransmitter;

    //���ջ�����
    ReceiveBuffer *m_pReceiveBuffer;
};

#endif
