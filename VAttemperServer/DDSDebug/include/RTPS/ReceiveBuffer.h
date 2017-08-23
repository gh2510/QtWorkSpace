/************************************************************
** �ļ�����ReceiveBuffer.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-16
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ReceiveBufferͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_RECEIVEBUFFER_H_INCLUDED_
#define _RTPS_RECEIVEBUFFER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
#include <semLib.h>
#else
#include "Windows.h"
#endif

class ReceiveBuffer 
{
public:
    //���캯��
    ReceiveBuffer(unsigned long ulLength);

    //��������
    virtual ~ReceiveBuffer();

    //��
    _RETURNCODE_T Read(char *pMessage, unsigned long ulLength);

    //д
    _RETURNCODE_T Write(char *pMessage, unsigned long ulLength, unsigned long ulAddress);

	//����ָ��ָ������ֶ�֮��
    _RETURNCODE_T FindPad();

private:
    //��������С
    unsigned long m_ulLength;

    //��ָ��λ��
    unsigned long m_ulReadPosition;

    //дָ��λ��
    unsigned long m_ulWritePosition;

    //������ һ��ѭ���Ŀռ�
    char *m_pBuffer;

	//���п�д�ռ�
	unsigned long m_ulAvailableLength;

    //�����ź���
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif

    //�������ź��� ��ʾ��������д������ݸ���
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemFull;
#else
	HANDLE m_hSemFull;
#endif

    //�������ź��� ��ʾ����������ʣ��Ŀռ����
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemEmpty;
#else
	HANDLE m_hSemEmpty;
#endif
};

#endif
