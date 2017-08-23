/************************************************************
** �ļ�����LocalDataGather.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-07-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����LocalDataGatherͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef LocalDataGather_hh
#define LocalDataGather_hh
#include"MRBasicTypes.h"
#include "MRReturnCode.h"

#include"dds/DomainParticipant.h"

#include "GetCPUPercentage.h"

#ifndef VXWORKS
#include <process.h>
#endif

struct _TIMESTAMP_T;
class GetCPUPercentage;
class LocalDataGather
{

private:
	//IP��ַ
	unsigned long m_ulIp;
	//������
	char* m_pHostName;

	//��ȡ������
	char* ObtainHostName(void);       //LocalDataGather.h
	//��ȡIP��ַ
	unsigned long ObtainIp (void);   //LocalDataGather.h

public:
	//���캯��
	LocalDataGather(void);   //LocalDataGather.h
	//��������
	~LocalDataGather(void);   //LocalDataGather.h

	//��ȡCPUռ����
	float  GetCPUOccupPercentage(void);   //LocalDataGather.h
	//��ȡ�ڴ�ռ����
	float  GetMemOccupPercentage (void);   //LocalDataGather.h
	
	//���ĳ�����̵������ڴ�ʹ�����
	unsigned long GetPMemoryInfo( DWORD dwProcessID );   //LocalDataGather.h

	//���ĳ�����̵������ڴ�ʹ�����
	unsigned long GetVMemoryInfo( DWORD dwProcessID );   //LocalDataGather.h

#ifdef VXWORKS
	//��ȡ�������ȼ�
	int  GetTaskPriority (int iTaskId);        //LocalDataGather.h
	//��ȡ���״̬
	_RETURNCODE_T  GetCompStatus (int iTaskId,_COMP_STATUS &Status);        //LocalDataGather.h
#else
	//��ȡ�������ȼ�
	int  GetTaskPriority (HANDLE iTaskId);        //LocalDataGather.h
	//��ȡ���״̬
	_RETURNCODE_T  GetCompStatus (HANDLE iTaskId,_COMP_STATUS &Status);        //LocalDataGather.h
	//��ȡĳ�����̵�CPU������
	GetCPUPercentage cProcessCPU;
#endif

	//��ȡʱ��
	_TIMESTAMP_T DDSGetCurrentTime(void);    //LocalDataGather.h
	//��ȡIP��ַ
	unsigned long  GetIp(void)
	{
		return m_ulIp;
	}       //LocalDataGather.h
	//��ȡ������
	char*  GetHostName(void) 
	{
		return m_pHostName;
	}        //LocalDataGather.h
};

#endif
