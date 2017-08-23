/************************************************************
** 文件名：GetCPUPercentage.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-07-15
** 修改人：无
** 日  期：无
** 描  述：GetCPUPercentage头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef VXWORKS  //移植
#include <Windows.h>
#endif

#ifndef VXWORKS

class GetCPUPercentage
{
private:
	CRITICAL_SECTION m_cs;  // 供多线程同步的临界区变量
	HANDLE m_hd;    // 空闲进程的句柄
	DWORD dwT1;     // 时间戳
	int iPercent;  // 最近一次计算的CPU占用率

	__int64 iOldp;
	__int64 FileTimeToInt64(const FILETIME& fileTime);   //GetCPUPercentage.h
	int GetTime(__int64& iProc);  // 得到进程占用的CPU时间 GetCPUPercentage.h
public:
	GetCPUPercentage();   //GetCPUPercentage.h
	~GetCPUPercentage();   //GetCPUPercentage.h

	int Get();  // 得到CPU占用率 GetCPUPercentage.h
};

#else
 class GetCPUPercentage
 {
 };

#endif