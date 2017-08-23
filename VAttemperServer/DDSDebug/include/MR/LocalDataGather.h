/************************************************************
** 文件名：LocalDataGather.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-07-26
** 修改人：无
** 日  期：无
** 描  述：LocalDataGather头文件
** 版  本：Version 0.1
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
	//IP地址
	unsigned long m_ulIp;
	//主机名
	char* m_pHostName;

	//获取主机名
	char* ObtainHostName(void);       //LocalDataGather.h
	//获取IP地址
	unsigned long ObtainIp (void);   //LocalDataGather.h

public:
	//构造函数
	LocalDataGather(void);   //LocalDataGather.h
	//析构函数
	~LocalDataGather(void);   //LocalDataGather.h

	//获取CPU占用率
	float  GetCPUOccupPercentage(void);   //LocalDataGather.h
	//获取内存占用率
	float  GetMemOccupPercentage (void);   //LocalDataGather.h
	
	//获得某个进程的物理内存使用情况
	unsigned long GetPMemoryInfo( DWORD dwProcessID );   //LocalDataGather.h

	//获得某个进程的虚拟内存使用情况
	unsigned long GetVMemoryInfo( DWORD dwProcessID );   //LocalDataGather.h

#ifdef VXWORKS
	//获取任务优先级
	int  GetTaskPriority (int iTaskId);        //LocalDataGather.h
	//获取组件状态
	_RETURNCODE_T  GetCompStatus (int iTaskId,_COMP_STATUS &Status);        //LocalDataGather.h
#else
	//获取任务优先级
	int  GetTaskPriority (HANDLE iTaskId);        //LocalDataGather.h
	//获取组件状态
	_RETURNCODE_T  GetCompStatus (HANDLE iTaskId,_COMP_STATUS &Status);        //LocalDataGather.h
	//获取某个进程的CPU利用率
	GetCPUPercentage cProcessCPU;
#endif

	//获取时间
	_TIMESTAMP_T DDSGetCurrentTime(void);    //LocalDataGather.h
	//获取IP地址
	unsigned long  GetIp(void)
	{
		return m_ulIp;
	}       //LocalDataGather.h
	//获取主机名
	char*  GetHostName(void) 
	{
		return m_pHostName;
	}        //LocalDataGather.h
};

#endif
