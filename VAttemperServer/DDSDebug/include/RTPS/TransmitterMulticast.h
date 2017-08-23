/************************************************************
** �ļ�����TransmitterMulticast.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-25
** �޸��ˣ���
** ��  �ڣ���
** ��  ����TransmitterMulticastͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_TRANSMITTERMULTICAST_H_INCLUDED_
#define _RTPS_TRANSMITTERMULTICAST_H_INCLUDED_

#include "BasicTypes.h"
#include "rtps/MessageTransmitter.h"

#ifndef VXWORKS   //��ֲ
#pragma comment(lib,"ws2_32.lib") 
#include <winsock.h>
#endif

typedef map<_SOCKET_T, unsigned long> _MULTIADDRMAP_T;
//���ձ��ĵ���󳤶� ����UDP
#ifdef VXWORKS
#define MAXSIZE 65536
#else
#define MAXSIZE 65536
#endif

class TransmitterMulticast : public MessageTransmitter 
{
public:
    //���캯��
    TransmitterMulticast(ReceiveBuffer *pReceiveBuffer);

    //��������
    virtual ~TransmitterMulticast();

    //����Socket API ���ͱ���
    _RETURNCODE_T SendMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength);

    //����Socket API ���Ͷಥ����
    _RETURNCODE_T SendMultiMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength);
        
    //����Socket API���ձ���
    _RETURNCODE_T ReceiveMessage();
    
    //��Ӽ�����ַ
    _RETURNCODE_T ReceiveAddrAdd(_LOCATOR_T ReceiveAddr);

    //��Ӽ����ಥ��ַ
    _RETURNCODE_T ReceiveMultiAddrAdd(_LOCATOR_T SourceAddr, _LOCATOR_T ReceiveAddr);
    
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

	//2013-10-16 hjy modify��������ƥ��ʱ�ӣ��տ�ʼ����255.255.255.255��socketʱ�����һ�� 
	int m_MatchTime;
    //
    _MULTIADDRMAP_T m_MultiAddrMap;
};

#endif
