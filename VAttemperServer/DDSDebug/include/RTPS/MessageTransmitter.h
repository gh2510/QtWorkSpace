/************************************************************
** �ļ�����MessageTransmitter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-16
** �޸��ˣ���
** ��  �ڣ���
** ��  ����MessageTransmitterͷ�ļ�
** ��  ����Version 0.1
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

//����
class ReceiveBuffer;

class MessageTransmitter 
{
public:
    //���캯��
    MessageTransmitter(ReceiveBuffer *pReceiveBuffer) 
    {
        m_pReceiveBuffer = pReceiveBuffer;

		//2013-10-15 hjy modify mutex�޸�
#ifdef VXWORKS
		memset(&m_hSemMutex, 0, sizeof(SEM_ID));	
		m_hSemMutex = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
#else
		m_hSemMutex = CreateMutex(NULL,FALSE,NULL);
#endif	
    }

    //��������
    virtual ~MessageTransmitter() 
    {
        m_Locator.clear();
    };

    //���� �麯���ṩ�ӿ�
    virtual _RETURNCODE_T SendMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength) = 0;

    //�ಥ���� �麯���ṩ�ӿ�
    virtual _RETURNCODE_T SendMultiMessage(
        _LOCATOR_T Source,
        _LOCATOR_T Destination,
        char *pMessage,
        unsigned long ulLength) = 0;

    //���� �麯���ṩ�ӿ�
    virtual _RETURNCODE_T ReceiveMessage() = 0;

    //��Ӽ�����ַ
    virtual _RETURNCODE_T ReceiveAddrAdd(_LOCATOR_T ReceiveAddr) = 0;

    //��Ӽ����ಥ��ַ
    virtual _RETURNCODE_T ReceiveMultiAddrAdd(_LOCATOR_T sourceAddr, _LOCATOR_T ReceiveAddr) = 0;

    //ɾ��������ַ
    virtual _RETURNCODE_T ReceiveAddrRemove(_LOCATOR_T ReceiveAddr) = 0;

    //��ʼ�����߳�/����
#ifdef VXWORKS   //��ֲ
    static _RETURNCODE_T TransmitRun(MessageTransmitter *pMessageTransmitter);
#else
	static DWORD WINAPI TransmitRun(LPVOID lpMessageTransmitter);
#endif

protected:
    //���ջ�����
    ReceiveBuffer *m_pReceiveBuffer;

    //������ַ�б�
    _LOCATOR_LIST_T m_Locator;

	//���ڻ������m_sendsocket
	//2013-10-15 hjy modify mutex�޸�
#ifdef VXWORKS
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
