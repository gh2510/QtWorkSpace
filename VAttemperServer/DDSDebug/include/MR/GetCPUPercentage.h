/************************************************************
** �ļ�����GetCPUPercentage.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-07-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����GetCPUPercentageͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef VXWORKS  //��ֲ
#include <Windows.h>
#endif

#ifndef VXWORKS

class GetCPUPercentage
{
private:
	CRITICAL_SECTION m_cs;  // �����߳�ͬ�����ٽ�������
	HANDLE m_hd;    // ���н��̵ľ��
	DWORD dwT1;     // ʱ���
	int iPercent;  // ���һ�μ����CPUռ����

	__int64 iOldp;
	__int64 FileTimeToInt64(const FILETIME& fileTime);   //GetCPUPercentage.h
	int GetTime(__int64& iProc);  // �õ�����ռ�õ�CPUʱ�� GetCPUPercentage.h
public:
	GetCPUPercentage();   //GetCPUPercentage.h
	~GetCPUPercentage();   //GetCPUPercentage.h

	int Get();  // �õ�CPUռ���� GetCPUPercentage.h
};

#else
 class GetCPUPercentage
 {
 };

#endif