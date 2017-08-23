/************************************************************
** �ļ�����TransmitterUnicast.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-16
** �޸��ˣ���
** ��  �ڣ���
** ��  ����TransmitterUnicastͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_TRANSMITTERUNICAST_H_INCLUDED_
#define _RTPS_TRANSMITTERUNICAST_H_INCLUDED_

#include "BasicTypes.h"
#include "rtps/MessageTransmitter.h"

#ifndef VXWORKS   //��ֲ
#pragma comment(lib,"ws2_32.lib") 
#include <winsock.h>
#endif

//���ձ��ĵ���󳤶� ����UDP
#define MAXSIZE 65536

class TransmitterUnicast : public MessageTransmitter 
{
public:
    //���캯��
    TransmitterUnicast(ReceiveBuffer *pReceiveBuffer);

    //��������
    virtual ~TransmitterUnicast();

    //����Socket API ���ͱ���
    _RETURNCODE_T SendMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength);

    //����Socket API���ձ���
    _RETURNCODE_T ReceiveMessage();

    //��Ӽ�����ַ
    _RETURNCODE_T ReceiveAddrAdd(_LOCATOR_T ReceiveAddr);

    //ɾ��������ַ
    _RETURNCODE_T ReceiveAddrRemove(_LOCATOR_T ReceiveAddr);

private:
    //���ձ���
    char *m_pMsgBuffer;

    //����socket
    _SEND_SOCKET_LIST m_SendSocket;

    //socket �󶨱��ص�IP��Port ��Ҫѭ������
    _SOCKET_LIST_T m_ReceiveSocket;

    //������socket���ֵ ����select������
    _SOCKET_T m_SocketMax;

    //������socket���� ����select����
    fd_set m_ReadSet;
};

#endif
